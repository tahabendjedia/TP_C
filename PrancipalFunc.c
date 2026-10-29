#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AbstractMachin.c"
#include <stdbool.h>


ptrCityNode findCity(Graph* graph, string name) { // A function to check if a city exist and return the pointer 
    ptrCityNode current = graph->head;
    while (current != NULL) {
        if (strcmp(getNameOfCity(current), name) == 0) { // compare between the names of cities 
            return current;
        }
        current = getNextOfCity(current);
    }
    return NULL;// Return null if it doesn't exist
}


void addCity(Graph* graph, string name) {
    if (findCity(graph, name) != NULL) { // To check that the city does not already exist 
        return; 
    }
    ptrCityNode newCity;
    AllocateCityNode(&newCity);
    Ass_NameOfCity(&newCity,strdup(name));
    Ass_AdjacencyListToCity(&newCity, NULL);
    Ass_NextCity(&newCity,graph->head);
    graph->head = newCity;// the city is added at the head of the gra
}


void addEdge(Graph* graph, string srcName, string destName, int distance) {
    ptrCityNode srcCity = findCity(graph, srcName);
    ptrCityNode destCity = findCity(graph, destName);


    if (srcCity == NULL) {
        addCity(graph, srcName);// if the origin city does not exist then we Add it 
        srcCity = findCity(graph, srcName);
    }

   
    if (destCity == NULL) {
        addCity(graph, destName); //if the destination   does not exist then we Add it
        destCity = findCity(graph, destName);
    }
 
    
    ptrAdjacencyNode newAdjNode;
    AllocateAdjacencyNode(&newAdjNode);
    Ass_CityToAdjacency(&newAdjNode,destCity);
    Ass_DistanceToAdjacency(&newAdjNode,distance);
    Ass_NextToAdjacency(&newAdjNode,getAdjacencyOfCity(srcCity));// connect the new adjecency city to the list of reachable cities 
    Ass_AdjacencyListToCity(&srcCity,newAdjNode);
}

void readGraphFromFile(Graph* graph, string filename) {
    FILE* file = fopen(filename, "r");

    char line[256];  // we read each line separately we use the variable Line as a placeHolder (buffer)
    while (fgets(line, sizeof(line), file)) {
        string token = strtok(line, " \t\n"); // strtok() is a commun function we use it to split the line and manipulate it according to the delimeters

        if (token == NULL) continue;  // at the first time we use the variable's name then after we use NULL to continue from where we stopped


        string srcName = token;
        addCity(graph, srcName);

        token = strtok(NULL, " \t\n");
        while (token != NULL) {
            string destName = token;
            token = strtok(NULL, " \t\n");
            if (token == NULL) break;

            int distance = atoi(token);
            addEdge(graph, srcName, destName, distance);

            token = strtok(NULL, " \t\n");
        }
    }

    fclose(file);
}

void displayGraph(Graph* graph) {
    ptrCityNode currentCity = graph->head;
    while (currentCity != NULL) {
        printf(" %s --> ", getNameOfCity(currentCity));

        ptrAdjacencyNode currentAdj = getAdjacencyOfCity(currentCity);
        while (currentAdj != NULL) {
            printf("(%s , %d) ", getNameOfCity(getCityOfAdjacency(currentAdj)), getDistanceOfAdjacency(currentAdj));
            currentAdj = getNextOfAdjacency(currentAdj);
        }
        printf("\n");

        currentCity = getNextOfCity(currentCity);
    }
}


void Disp(ptrVisitedNode p,string name) {
    while (strcmp(name,p->city->name)!=0) {
        printf(" %s", p->city->name);
        p = p->next;
    }
}


ptrVisitedNode reachableCities(Graph* graph, string startName) {
    ptrCityNode start = findCity(graph, startName);
    if (start == NULL) {
        printf("City not found.\n");
        return NULL;
    }

    ptrQueueNode Head=NULL;
    ptrQueueNode Tail=NULL;
    ptrQueueNode newNode;
    AllocateQueueNode(&newNode);
    newNode->city = start;
    newNode->next = NULL;
    Tail = Head = newNode;

    ptrVisitedNode visitedList = NULL;
    addToVisited(&visitedList, start);
    while (Head != NULL) {
        ptrQueueNode currentQueueNode = Head;
        ptrCityNode currentCity = currentQueueNode->city;

        Head = Head->next;
        if (Head == NULL) Tail = NULL;
        ptrAdjacencyNode adjNode = currentCity->adjacencyList;
        while (adjNode != NULL) {
            ptrCityNode neighbor = adjNode->city;
            if (!isVisited(visitedList, neighbor)) {
                addToVisited(&visitedList, neighbor);

                ptrQueueNode newQueueNode ;
                AllocateQueueNode(&newQueueNode);
                newQueueNode->city = neighbor;
                newQueueNode->next = NULL;

                if (Tail == NULL) {
                    Head = Tail = newQueueNode;
                } else {
                    Tail->next = newQueueNode;
                    Tail = newQueueNode;
                }
            }
            adjNode = adjNode->next;
        }

        free(currentQueueNode);
    }

    return visitedList;
}




int pathExists(Graph* graph, string srcName, string destName) {
   ptrVisitedNode Head = reachableCities(graph,srcName); // we saerch in the list of reachable cities
   ptrVisitedNode p=Head;
   while (p!=NULL) {
    if (strcmp( p->city->name,destName)==0){
        return 1;
    }
    p = p->next;
 }
 return 0;
       }    


            // Helper to get the number of cities (for simplicity, use linked list traversal)
int countCities(Graph *graph) {
    int count = 0;
    ptrCityNode current = graph->head;
    while (current) {
        count++;
        current = getNextOfCity(current);
    }
    return count;
}


       // Returns index of the city with minimum distance not visited yet
int minDistance(int dist[], bool visited[], int numCities) {
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < numCities; i++) {
        if (!visited[i] && dist[i] < min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void findBestPath(Graph *graph, string srcName, string destName) {
    int numCities = countCities(&(*graph));
    if (numCities == 0) return;

    // Create arrays for distances, visited flags, and previous nodes , we take maximum 100 city 
    int dist[100];
    bool visited[100];
    int prev[100];

    ptrCityNode cities[100];
    ptrCityNode current = graph->head;
    for (int i = 0; i < numCities; i++) {
        cities[i] = current;
        dist[i] = INT_MAX;           // we initialize for every city the distance as max (infinity) , and not visited , and without prev
        visited[i] = false;
        prev[i] = -1;
        current = getNextOfCity(current);
    }

    // Get index of source and destination
    int srcIdx = -1, destIdx = -1;
    for (int i = 0; i < numCities; i++) {
        if (strcmp(getNameOfCity(cities[i]), srcName) == 0) srcIdx = i;
        if (strcmp(getNameOfCity(cities[i]), destName) == 0) destIdx = i;
    }

    if (srcIdx == -1 || destIdx == -1) {
        printf("City not found.\n");
        return;
    }

    dist[srcIdx] = 0;  //we initialize the distance for the start point with 0  

    for (int count = 0; count < numCities - 1; count++) {
        int u = minDistance(dist, visited, numCities); //find the new city with shortest distance
        if (u == -1) break;
        visited[u] = true; // change flag to visited(true) instead of not visited

        ptrAdjacencyNode adj = getAdjacencyOfCity(cities[u]) ; // we prossceed to the nested cities
        while (adj != NULL) {
            int v = -1;
            for (int i = 0; i < numCities; i++) {
                if (cities[i] == getCityOfAdjacency(adj)) {
                    v = i;
                    break;
                }
            }

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + getDistanceOfAdjacency(adj) < dist[v]) {
                dist[v] = dist[u] + getDistanceOfAdjacency(adj); // update the distance when finding shortest path 
                prev[v] = u; //we save the previous city 
            }

            adj = getNextOfAdjacency(adj);
        }
    }

    // Reconstruct and print the path
    if (dist[destIdx] == INT_MAX) {
        printf("No path from %s to %s\n", srcName, destName); // in case the distance still at max then there is no path 
        return;
    }

    printf("Shortest distance: %d\nPath: ", dist[destIdx]); // print distance 
    int path[100], count = 0, temp = destIdx;
    while (temp != -1) {
        path[count++] = temp;
        temp = prev[temp];
    }

    for (int i = count - 1; i >= 0; i--) {
    printf("%s", getNameOfCity(cities[path[i]]));
        if (i != 0) printf(" --> ");
    }
    printf("\n");
}
void removeCity(Graph *graph, string name){
    ptrCityNode City = findCity(graph, name);
    //printf("%s",City->name);
   
    if (graph->head == NULL) { 
        return;  // If graph is empty, do nothing
    }
   

    if (City == NULL) {
        printf("This city does not exist!\n");
        return;
    }
   

    
    ptrCityNode prev = NULL ;
    ptrCityNode current = graph->head;
    
    while (current != NULL && current != City) { // Find the city in the linked list
        prev = current;
        current = getNextOfCity(current);
    }

    if (prev == NULL) { // The city is the head
        graph->head = getNextOfCity(current);
    } else {
        Ass_NextCity(&prev, getNextOfCity(current));
    }
    
    // Free adjacency list of city being deleted
    ptrAdjacencyNode adj = getAdjacencyOfCity(City);
    while (adj != NULL) {
        ptrAdjacencyNode temp = adj;
        adj = getNextOfAdjacency(adj);
        free(temp);
    }
    
    free(City); // Finally, free city node
    printf("City %s deleted successfully!\n", name);
}
