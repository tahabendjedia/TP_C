#include <stdlib.h>
#include <string.h>

typedef char* string;

typedef struct AdjacencyNode {
    struct CityNode* city; 
    int distance;          
    struct AdjacencyNode* next; 
} AdjacencyNode;


typedef struct CityNode {
    string name;                
    AdjacencyNode* adjacencyList; 
    struct CityNode* next;    
} CityNode;

typedef struct Graph{
    CityNode* head; 
} Graph;

typedef struct VisitedNode {
    CityNode* city;           
    struct VisitedNode* next;  
} VisitedNode;


typedef struct QueueNode {
    CityNode* city;
    struct QueueNode* next;
} QueueNode;

typedef QueueNode* ptrQueueNode;
typedef VisitedNode* ptrVisitedNode;
typedef CityNode* ptrCityNode;
typedef AdjacencyNode* ptrAdjacencyNode;

/* ------------------CityNode Abstract-------------------- */
void AllocateCityNode(ptrCityNode* NewCity){
     *NewCity = (ptrCityNode)malloc(sizeof(CityNode));
}


string getNameOfCity(ptrCityNode city){
    return city->name;
}

ptrCityNode getNextOfCity(ptrCityNode city){
    return city->next;
}

ptrAdjacencyNode getAdjacencyOfCity(ptrCityNode city){
    return city->adjacencyList;
}

void Ass_NameOfCity(ptrCityNode* AdrCity,string name){
    (*AdrCity)->name=name;
}

void Ass_AdjacencyListToCity(ptrCityNode* AdrCity,ptrAdjacencyNode Adjacency){
    (*AdrCity)->adjacencyList=Adjacency;
}

void Ass_NextCity(ptrCityNode* AdrCity,ptrCityNode NextCity){
    (*AdrCity)->next=NextCity;
}

/* ---------------AdjacencyNode Abstract----------------- */

void AllocateAdjacencyNode(ptrAdjacencyNode* NewAdjacency){
    *NewAdjacency = (ptrAdjacencyNode)malloc(sizeof(AdjacencyNode));
}

ptrCityNode getCityOfAdjacency(ptrAdjacencyNode Adjacency){
    return Adjacency->city;
}

int getDistanceOfAdjacency(ptrAdjacencyNode Adjacency){
    return Adjacency->distance;
}

ptrAdjacencyNode getNextOfAdjacency(ptrAdjacencyNode Adjacency){
    return Adjacency->next;
}

void Ass_CityToAdjacency(ptrAdjacencyNode* AdrAdjacency,ptrCityNode originCity){
    (*AdrAdjacency)->city=originCity;
}

void Ass_DistanceToAdjacency(ptrAdjacencyNode* AdrAdjacency, int distance){
    (*AdrAdjacency)->distance = distance;
}

void Ass_NextToAdjacency(ptrAdjacencyNode* AdrAdjacency,ptrAdjacencyNode Next){
    (*AdrAdjacency)->next=Next;
}

/* ----------------VisitedNode abstract ------------------ */

void AllocateVisitedNode(ptrVisitedNode* NewCity){
    *NewCity = (ptrVisitedNode)malloc(sizeof(VisitedNode));
}


ptrCityNode getVisitedCity(VisitedNode list){
    return list.city;
}

ptrVisitedNode getNextVisitedCity(VisitedNode list){
    return list.next;
}

void Ass_VisitedCity(ptrVisitedNode* list,ptrCityNode City){
    (*list)->city=City;
}

void Ass_NextVisitedCity(ptrVisitedNode* list,ptrVisitedNode next){
    (*list)->next=next;
}

int isVisited(ptrVisitedNode list, ptrCityNode city) {
    ptrVisitedNode current = list;
    while (current != NULL) {
        if (getVisitedCity(*current)== city) {
            return 1;
        }
        current =getNextVisitedCity(*current);
    }
    return 0;
}

void addToVisited(ptrVisitedNode* list, ptrCityNode city) {
    if (isVisited(*list, city)) return;
    ptrVisitedNode newNode;
    AllocateVisitedNode(&newNode);
    Ass_VisitedCity(&newNode,city);
    Ass_NextVisitedCity(&newNode,*list);
    *list = newNode;
}

/* ----------------------queue Abstract ----------------- */

void AllocateQueueNode(ptrQueueNode* new){
    *new=(ptrQueueNode)malloc(sizeof(QueueNode));
}

void FreeVisitedList( ptrVisitedNode* visitedList){
    ptrVisitedNode currentVisited = *visitedList;
    while (currentVisited != NULL) {
        ptrVisitedNode temp = currentVisited;
        currentVisited = currentVisited->next;
        free(temp);
    }
}

/* ------------------------------------------------------ */




void initGraph(Graph* graph) {
    graph->head = NULL;
}