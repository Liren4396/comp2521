// Implementation of the Agent ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Agent.h"
#include "Map.h"

#define no_stamina_consume 0
#define init_num_visit 0
#define init_prev_visit -1


// This struct stores information about an individual agent and can be
// used to store information that the agent needs to remember.
struct agent {
    char *name;
    int startLocation;
    int location;
    int maxStamina; // max stamina
    int stamina;    // current stamina
    int strategy;
    Map map;
    
    // TODO: Add more fields here as needed
    int *num_visit; // number of visits count
    bool *is_visited; // for strategy Dfs
    int *previous_visit; // previous visit
    int *previous_visit_len; // previous visit length
    int thief_location;
};

// Queue Struct 
typedef int Item;

typedef struct node *Node;
struct node {
	Item item;
	Node next;
};
typedef struct queue *Queue;
struct queue {
	Node head;
	Node tail;
	int  size;
};



void initialize_malloc_var(Agent agent, Map m);
Move chooseRandomMove(Agent agent, Map m);
int filterRoads(Agent agent, Road roads[], int numRoads,
                       Road legalRoads[]);
Move choose_least_visited(Agent agent, Map m);
Move choose_DFS(Agent agent, Map m);
void insertion_sort(int numLegalRoads, Road legalRoads[numLegalRoads]);
void least_visited_find_min(int *min, int *min_pos, int *min_stamina, 
Agent agent,int numLegalRoads, Road legalRoads[numLegalRoads]);
static void BFS_import(int nV, int pred[nV], Agent agent, Map m);
static int count_visited_city_num(Agent agent, Map m);
static void DFS_reset_agent_status(Agent agent, Map m);
static Move find_min_roads_in_DFS(Road roads, Agent agent);
bool QueueIsEmpty(Queue q);
Item QueueDequeue(Queue q);
Node newNode(Item it);
void QueueEnqueue(Queue q, Item it);
void QueueFree(Queue q);
Queue QueueNew(void);


///////////////////////////////////////////////////////////
//                        Queue                          //
///////////////////////////////////////////////////////////

/**
 * Creates a new empty queue
 */
Queue QueueNew(void) {
	Queue q = malloc(sizeof(*q));
	if (q == NULL) {
		fprintf(stderr, "couldn't allocate Queue\n");
		exit(EXIT_FAILURE);
	}
	
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;
	return q;
}
/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q) {
	Node curr = q->head;
	while (curr != NULL) {
		Node temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(q);
}
/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it) {
	Node n = newNode(it);
	if (q->size == 0) {
		q->head = n;
	} else {
		q->tail->next = n;
	}
	q->tail = n;
	q->size++;
}

Node newNode(Item it) {
	Node n = malloc(sizeof(*n));
	if (n == NULL) {
		fprintf(stderr, "couldn't allocate Node\n");
		exit(EXIT_FAILURE);
	}
	
	n->item = it;
	n->next = NULL;
	return n;
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q) {
	assert(q->size > 0);
	
	Node newHead = q->head->next;
	Item it = q->head->item;
	free(q->head);
	q->head = newHead;
	if (newHead == NULL) {
		q->tail = NULL;
	}
	q->size--;
	return it;
}
/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q) {
	return q->size == 0;
}


///////////////////////////////////////////////////////////


// initialize malloc variable created by myself
void initialize_malloc_var(Agent agent, Map m) {
    for (int i = 0; i < MapNumCities(m); i++) {
        agent->previous_visit[i] = init_prev_visit;
        agent->previous_visit[i] = init_prev_visit;
        agent->num_visit[i] = init_num_visit;
        agent->is_visited[i] = false;
    }
}


/**
 * Creates a new agent
 */
Agent AgentNew(int start, int stamina, int strategy, Map m, char *name) {
    if (start >= MapNumCities(m)) {
        fprintf(stderr, "error: starting city (%d) is invalid\n", start);
        exit(EXIT_FAILURE);
    }
    
    Agent agent = malloc(sizeof(struct agent));
    if (agent == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    agent->startLocation = start;
    agent->location = start;
    agent->maxStamina = stamina;
    agent->stamina = stamina;
    agent->strategy = strategy;
    agent->map = m;
    agent->name = strdup(name);
    agent->previous_visit = malloc(sizeof(int *) * MapNumCities(m));
    agent->previous_visit_len = malloc(sizeof(int *) * MapNumCities(m));
    agent->num_visit = malloc(sizeof(int*) * MapNumCities(m));
    agent->is_visited = malloc(sizeof(bool) * MapNumCities(m));
    initialize_malloc_var(agent, m);
    agent->num_visit[agent->startLocation] = 1;
    agent->is_visited[agent->location] = true;
    agent->thief_location = -1;
    return agent;
}

/**
 * Frees all memory associated with the agent
 * NOTE: You should not free the map because the map is owned by the
 *       main program, and the main program will free it
 */
void AgentFree(Agent agent) {
    // TODO: You may need to update this to free any extra memory you use
    free(agent->name);
    free(agent->num_visit);
    free(agent->is_visited);
    free(agent->previous_visit);
    free(agent->previous_visit_len);
    free(agent);
}

////////////////////////////////////////////////////////////////////////
// Making moves



// Sort the roads using insertion sort
void insertion_sort(int numLegalRoads, 
Road legalRoads[numLegalRoads]) {
    
    for (int i = 1; i < numLegalRoads; i++) {
        Road r = legalRoads[i];
        int j = i;
        while (j > 0 && r.to < legalRoads[j - 1].to) {
            legalRoads[j] = legalRoads[j - 1];
            j--;
        }
        legalRoads[j] = r;
    }
}

static void change_min(int *min, int *min_pos, 
int *min_stamina, Agent agent, Road r) {
    *min_pos = r.to;
    *min = agent->num_visit[r.to];
    *min_stamina = r.length;
}

//1.choose the min viseted city
// 2.if num_visited is same, choose least stamina city
// 3.if both of above two are same, choose lowest id city 
void least_visited_find_min(int *min, int *min_pos, int *min_stamina, 
Agent agent,int numLegalRoads, Road legalRoads[numLegalRoads]) {
    for (int i = 0; i < numLegalRoads; i++) {
        
        Road r = legalRoads[i];
        if (*min < agent->num_visit[r.to]) {
            continue;
        } else if (*min > agent->num_visit[r.to]) {
            change_min(min, min_pos, min_stamina, agent, r);
        } else if (*min_stamina < r.length) {
            continue;
        } else if (*min_stamina > r.length) {
            change_min(min, min_pos, min_stamina, agent, r);
        } else if (*min_pos > r.to) {
            change_min(min, min_pos, min_stamina, agent, r);
        }
        
    }
}


Move choose_least_visited(Agent agent, Map m) {
    Road *roads = malloc(MapNumCities(m) * sizeof(Road));
    Road *legalRoads = malloc(MapNumCities(m) * sizeof(Road));
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);
    Move move;
    if (numLegalRoads > 0) {
        insertion_sort(numLegalRoads, legalRoads);
        
        int min_pos = legalRoads[0].to;
        int min_stamina = legalRoads[0].length;
        int min = agent->num_visit[legalRoads[0].to];
        least_visited_find_min(&min, &min_pos, &min_stamina, 
        agent, numLegalRoads,legalRoads);
        // if agent has enough stamina
        if (min_stamina <= agent->stamina) {
            move = (Move){min_pos, min_stamina};
            
        } else {
            move = (Move){agent->location, no_stamina_consume};
        }
    } else {
        // The agent must stay in the same location
        move = (Move){agent->location, no_stamina_consume};
    }
    free(legalRoads);
    free(roads);
    return move;
}




// Stage 2 : DFS
Move choose_DFS(Agent agent, Map m) {
    Road *roads = malloc(MapNumCities(m) * sizeof(Road));
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);
    Move move;
    if (numRoads > 0) {
        int count = count_visited_city_num(agent, m);
        if (count == MapNumCities(m)) {
            DFS_reset_agent_status(agent, m);
        } else {
            int num_visited = 0;
            for (int i = 0; i < numRoads; i++) {
                if (agent->is_visited[roads[i].to] == false) {
                    move = find_min_roads_in_DFS(roads[i], agent);
                    break;
                } else {
                    num_visited++;
                }
            }
            if (num_visited == numRoads) {
                move = find_min_roads_in_DFS(roads[0], agent);
            }
        }
    } else {
        move = (Move){agent->location, no_stamina_consume};
    }
    free(roads);
    return move;
    


}


// reset all the cities to that not been visited
static void DFS_reset_agent_status(Agent agent, Map m) {
    for (int i = 0; i < MapNumCities(m); i++) {
        agent->previous_visit[i] = -1;
    }
    for (int i = 0; i < MapNumCities(m); i++) {
        agent->previous_visit[i] = -1;
    }
    for (int i = 0; i < MapNumCities(m); i++) {
        agent->is_visited[i] = false;
    }
    agent->is_visited[agent->location] = true;
}

// count the number of city has been visited
static int count_visited_city_num(Agent agent, Map m) {
    int count = 0;
    for (int i = 0; i < MapNumCities(m); i++) {
        if (agent->is_visited[i] == true) {
            count++;
        }
    }
    return count;
}

// if the agent has enough stamina to move, then move
// otherwise stay in the same place
static Move find_min_roads_in_DFS(Road roads, Agent agent) {
    if (agent->stamina < roads.length) {
        return (Move){agent->location, no_stamina_consume};
    } else {
        agent->previous_visit[roads.to] = agent->location;
        agent->previous_visit_len[roads.to] = roads.length;
        return (Move){roads.to, roads.length};
    }
}


// use queue struct to do BFS search
static void BFS_import(int nV, int pred[nV], Agent agent, Map m) {
    bool found = false;
    Queue q = QueueNew();
    QueueEnqueue(q, agent->location);
    while (!found && !QueueIsEmpty(q)) {
        Item curr = QueueDequeue(q);
        for (int i = 0; i < nV; i++) {
            if (MapContainsRoad(m, curr, i) && pred[i] == -1) {
                pred[i] = curr;
                if (i == agent->thief_location) {
                    found = true;
                }
                QueueEnqueue(q, i);
            }
        }
    }
    QueueFree(q);
}



// from the agent current place to destination place(agent->thief_location)
static Move shortest_path(Agent agent, Map m) {
    Road *roads = malloc(MapNumCities(m) * sizeof(Road));
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);
    if (numRoads > 0) {
        int nV = MapNumCities(m);
        Item pred[nV];
        for (int i = 0; i < MapNumCities(m); i++) {
            pred[i] = -1;
        }
        pred[agent->location] = agent->location;
        BFS_import(nV, pred, agent, m);
        int dist[nV];
        int distance = 0;
        int curr = agent->thief_location;
        while (curr != agent->location) {
            dist[distance] = curr;
            if (curr == agent->location) {
                break;
            }
            distance++;
            curr = pred[curr];
        }
        if (distance == 1) {
            agent->thief_location = -1;
        }
        int stamina_cost = MapContainsRoad(m, 
        agent->location, dist[distance - 1]);
        if (stamina_cost > agent->stamina) {
            free(roads);
            return (Move){agent->location, no_stamina_consume};
        } else {
            free(roads);
            return (Move){dist[distance - 1], stamina_cost};
        }
    } else {
        free(roads);
        return (Move){agent->location, no_stamina_consume};
    }
}







/**
 * Calculates the agent's next move
 */
Move AgentGetNextMove(Agent agent, Map m) {
    if (agent->thief_location != -1) {
            return shortest_path(agent, m);
        }
    switch (agent->strategy) {
        
        case STATIONARY: return (Move){agent->location, no_stamina_consume};
        case RANDOM:     return chooseRandomMove(agent, m);
        // TODO: Implement more strategies here
        case CHEAPEST_LEAST_VISITED: return choose_least_visited(agent, m);
        case DFS: return choose_DFS(agent, m);
        default:
            printf("error: strategy not implemented yet\n");
            exit(EXIT_FAILURE);
    }
}




Move chooseRandomMove(Agent agent, Map m) {
    Road *roads = malloc(MapNumCities(m) * sizeof(Road));
    Road *legalRoads = malloc(MapNumCities(m) * sizeof(Road));

    // Get all roads to adjacent cities
    int numRoads = MapGetRoadsFrom(m, agent->location, roads);

    // Filter out roads that the agent does not have enough stamina for
    int numLegalRoads = filterRoads(agent, roads, numRoads, legalRoads);

    Move move;
    if (numLegalRoads > 0) {
        // Sort the roads using insertion sort
        insertion_sort(numLegalRoads, legalRoads);

        // nextMove is randomly chosen from the legal roads
        int k = rand() % numLegalRoads;
        move = (Move){legalRoads[k].to, legalRoads[k].length};
    } else {
        // The agent must stay in the same location
        move = (Move){agent->location, no_stamina_consume};
    }
    
    free(legalRoads);
    free(roads);
    return move;
}

// Takes an array with all the possible roads and puts the ones the agent
// has enough stamina for into the legalRoads array
// Returns the number of legal roads
int filterRoads(Agent agent, Road roads[], int numRoads,
                       Road legalRoads[]) {
    int numLegalRoads = 0;
    for (int i = 0; i < numRoads; i++) {
        if (roads[i].length <= agent->stamina) {
            legalRoads[numLegalRoads++] = roads[i];
        }
    }
    return numLegalRoads;
}

/**
 * Executes a given move by updating the agent's internal state
 */
void AgentMakeNextMove(Agent agent, Move move) {
    if (move.to == agent->location) {
        agent->stamina = agent->maxStamina;
    } else {
        agent->stamina -= move.staminaCost;
    }
    agent->location = move.to;
    agent->is_visited[move.to] = true;
    agent->num_visit[agent->location]++;
}

////////////////////////////////////////////////////////////////////////
// Gets information about the agent
// NOTE: It is expected that these functions do not need to be modified

/**
 * Gets the name of the agent
 */
char *AgentName(Agent agent) {
    return agent->name;
}

/**
 * Gets the current location of the agent
 */
int AgentLocation(Agent agent) {
    return agent->location;
}

/**
 * Gets the amount of stamina the agent currently has
 */
int AgentStamina(Agent agent) {
    return agent->stamina;
}

////////////////////////////////////////////////////////////////////////
// Learning information

/**
 * Tells the agent where the thief is
 */
void AgentGainInfo(Agent agent, int thiefLocation) {
    agent->thief_location = thiefLocation;
}

////////////////////////////////////////////////////////////////////////
// Displaying state

/**
 * Prints information about the agent (for debugging purposes)
 */
void AgentShow(Agent agent) {
///
}

////////////////////////////////////////////////////////////////////////
