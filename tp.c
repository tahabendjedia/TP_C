#include "PrancipalFunc.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main() {
    Graph graph;
    initGraph(&graph);
    readGraphFromFile(&graph, "cities.txt");

    int choice;
    int dist;
    char name[256],src[256],dest[256];
    do {
        printf("\nMenu:\n");
        printf("1. Display the graph\n");
        printf("2. Show reachable cities\n");
        printf("3. Check path between two cities\n");
        printf("4. Find best path\n");
        printf("5. Add a city\n");
        printf("6. Add a path\n");
        printf("7. Delete a city\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                displayGraph(&graph);
                break;
                //-----------------------------------------------------------
            case 2:
                printf("Enter city name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                ptrVisitedNode visitedList = NULL;
                printf("\nReachable cities from %s are : ",name);
                Disp(reachableCities(&graph,name),name);
                break; 
                //-------------------------------------------------------------- 
                
            case 3:
                printf("Enter source city: ");
                fgets(src, sizeof(src), stdin);
                src[strcspn(src, "\n")] = '\0';
                printf("Enter destination city: ");
                fgets(dest, sizeof(dest), stdin);
                dest[strcspn(dest, "\n")] = '\0';
                if (pathExists(&graph, src, dest)) {
                    printf("Path exists.\n");
                } else {
                    printf("No path exists.\n");
                }
                break;  
                //----------------------------------------------------------------
            
            case 4:
            printf("\n Enter the departer city :");
            fgets(src,50,stdin);
            src[strcspn(src, "\n")] = '\0';
            printf("\n Enter the arrival city :");
            fgets(dest,50,stdin);
            dest[strcspn(dest, "\n")] = '\0';
            findBestPath(&graph,src,dest);
            break;
            //------------------------------------------------------------------
             case 5:
             printf("\nThe city's name is : ");
             fgets(name, sizeof(name), stdin);
             name[strcspn(name, "\n")] = '\0';
             addCity(&graph,name);
             break;

            //------------------------------------------------------------------

            case 6:
          
            printf("\nEnter source city: ");
                fgets(src, sizeof(src), stdin);
                src[strcspn(src, "\n")] = '\0';
                printf("\nEnter destination city: ");
                fgets(dest, sizeof(dest), stdin);
                dest[strcspn(dest, "\n")] = '\0';
                printf("\n enter the distance between them :  ");
                scanf("%d",&dist);
                addEdge(&graph,src,dest,dist);
                break;

            //------------------------------------------------------------------
            case 7:
            printf("\nThe city's name is : ");
            fgets(name, sizeof(name), stdin);
             removeCity(&graph,name);
             break;

            
            case 8:
                printf("Exiting...\n");
                break;
                //---------------------------------------------------------------
            default:
                printf("Invalid choice.\n");
        
        }
    
    } while (choice != 8);

    return 0;

}
