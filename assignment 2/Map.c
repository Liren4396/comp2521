// Implementation of the Map ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Map.h"
#define MAX_LINE 100
#define MAX_CITY_NAME 30


struct map { 

    int nV;
    int nE;
    char **name;
    Road **roads;

};






/**
 * Creates a new map with the given number of cities
 * Assumes that numCities is positive
 */
Map MapNew(int numCities) {
    struct map *map = malloc(sizeof(struct map));
    assert(map != NULL);
    map->nV = numCities;
    map->nE = 0;
    map->roads = malloc(numCities * sizeof(Road *));
    map->name = malloc(numCities * sizeof(char *));
    
    assert(map->roads != NULL);
    for (int i = 0; i < numCities; i++) {
        Road *new = malloc(sizeof(Road) * numCities);
        map->roads[i] = new;
        assert(map->roads[i] != NULL);
        map->name[i] = malloc(sizeof(MAX_CITY_NAME));
        assert(map->name[i] != NULL);
        
        for (int j = 0; j < numCities; j++) {
            map->roads[i][j].length = -1;
            map->roads[i][j].from = -1;
            map->roads[i][j].to = -1;
        }
        
    }
    return map;
}

/**
 * Frees all memory associated with the given map
 */
void MapFree(Map m) {

    for (int i = 0; i < m->nV; i++) {
        if (m->name[i] != NULL) {
            free(m->name[i]);
        }
        m->name[i] = NULL;
        if (m->roads[i] != NULL) {
            free(m->roads[i]);
        }
        m->roads[i] = NULL;
    }
    free(m->name);
    m->name = NULL;
    free(m->roads);
    m->roads = NULL;
    free(m);
    
    m = NULL;
}

/**
 * Returns the number of cities on the given map
 */
int MapNumCities(Map m) {
    return m->nV;
}

/**
 * Returns the number of roads on the given map
 */
int MapNumRoads(Map m) {
    return m->nE;
}

/**
 * Inserts a road between two cities with the given length
 * Does nothing if there is already a road between the two cities
 * Assumes that the cities are valid and are not the same
 * Assumes that the length of the road is positive
 */
void MapInsertRoad(Map m, int city1, int city2, int length) {
    assert(m != NULL);
    assert(city1 != city2);

    
    if (m->roads[city1][city2].length != length || m->roads[city1][city2].from != city1
    || m->roads[city1][city2].to != city2) {
        m->roads[city1][city2].to = city2;
        m->roads[city1][city2].from = city1;
        m->roads[city1][city2].length = length;
        m->roads[city2][city1].to = city1;
        m->roads[city2][city1].from = city2;
        m->roads[city2][city1].length = length;
        m->nE++;
    }
}

/**
 * Sets the name of the given city
 */
void MapSetName(Map m, int city, char *name) {
    strcpy(m->name[city], name);
}

/**
 * Returns the name of the given city
 */
char *MapGetName(Map m, int city) {
    
    return m->name[city];
}

/**
 * Checks if there is a road between the two given cities
 * Returns the length of the road if there is a road, and 0 otherwise
 */
int MapContainsRoad(Map m, int city1, int city2) {
    if (m->roads[city1][city2].from == city1
    && m->roads[city1][city2].to == city2
    && m->roads[city1][city2].length != -1) {
        return m->roads[city1][city2].length;
    } else {
        return 0;
    }
    
}

/**
 * Returns the number of roads connected to the given city and stores
 * them in the given roads array. The `from` field should be equal to
 * `city` for all the roads in the array.
 * Assumes that the roads array is large enough to store all the roads
 */
int MapGetRoadsFrom(Map m, int city, Road roads[]) {
    int count = 0;
    for (int i = 0; i < m->nV; i++) {
        if (m->roads[city][i].length != -1
        && m->roads[city][i].from == city
        && m->roads[city][i].from != m->roads[city][i].to) {
            roads[count] = m->roads[city][i];
            count++;
        }
    }
    return count;
}

/**
 * Displays the map
 * !!! DO NOT EDIT THIS FUNCTION !!!
 * This function will work once the other functions are working
 */
void MapShow(Map m) {
    printf("Number of cities: %d\n", MapNumCities(m));
    printf("Number of roads: %d\n", MapNumRoads(m));
    
    Road *roads = malloc(MapNumRoads(m) * sizeof(Road));
    if (roads == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);    
    }
    for (int i = 0; i < MapNumCities(m); i++) {
        printf("[%d] %s has roads to:", i, MapGetName(m, i));
        int numRoads = MapGetRoadsFrom(m, i, roads);
        for (int j = 0; j < numRoads; j++) {
            if (j > 0) {
                printf(",");
            }
            printf(" [%d] %s (%d)", roads[j].to, MapGetName(m, roads[j].to),
                   roads[j].length);
        }
        printf("\n");
    }
    free(roads);
}

