// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Place.h"
#include "PQ.h"

////////////////////////////////////////////////////////////////////////
// Your task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */

typedef struct graph *Grid;
struct graph {
    int nV;
    int nE;
    double **edges;
};


int planGrid1(Place cities[], int numCities, Place powerPlant,
              PowerLine powerLines[]) {
    Graph g = GraphNew(numCities + 1);
    int index = numCities;
    
    for (int i = 0; i < numCities; i++) {
        double weight = sqrt(pow((cities[i].x - powerPlant.x), 2) + pow((cities[i].y - powerPlant.y), 2));
        Edge e = {i, index, weight};
        GraphInsertEdge(g, e);
        for (int j = i + 1; j < numCities; j++) {
            weight = sqrt(pow((cities[i].x - cities[j].x), 2) + pow((cities[i].y - cities[j].y), 2));
            Edge e_1 = {i, j, weight};
            GraphInsertEdge(g, e_1);
        }
    }
    Graph MST = GraphMST(g);
    int k = 0;
    for (int i = 0; i < numCities; i++) {
        if (GraphIsAdjacent(MST, i, index)) {
            PowerLine pLine = {cities[i], powerPlant};
            powerLines[k] = pLine;
            k++;
        }
        for (int j = i + 1; j < numCities; j++) {
            if (GraphIsAdjacent(MST, i, j)) {
                PowerLine pLine = {cities[i], cities[j]};
                powerLines[k] = pLine;
                k++;
            }
        }
    }
    GraphFree(g);
    GraphFree(MST);
    
    return numCities;
}

////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(Place cities[], int numCities,
              Place powerPlants[], int numPowerPlants,
              PowerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
