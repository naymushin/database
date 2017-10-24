/*
 *  Hash-tables
 *  Author: Naymushin D.P.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "map.h"

/* Prototype of function that process name of country */
void undecorate_name(char * name);

/* Main function */
int main(int argc, char * argv[]) {
    
    /* Loading list */
    COUNTRY ** map = map_load();

    char *cmd = (char*)malloc(11 * sizeof(char));
    char *name = (char*)malloc(41 * sizeof(char));

    unsigned int population;
    unsigned int area;

    cmd[10] = '\0'; 
    name[40] = '\0';    

    while(1) {
        printf("\nEnter command with parameters delimited with space: ");
        scanf("%s", cmd);

        if(strcmp(cmd, "add") == 0) {
        
            scanf("%s", name);
            undecorate_name(name);

            scanf("%d", &population);
            scanf("%d", &area);

            map_add(map, name, population, area);

        } else if (strcmp(cmd, "delete") == 0) {

            scanf("%s", name);
            undecorate_name(name);

            map_delete(map, name);
            
        } else if (strcmp(cmd, "dump") == 0) {

            map_dump(map);
            
        } else if (strcmp(cmd, "view") == 0) {

            scanf("%s", name);
            undecorate_name(name);

            map_view(map, name);
            
        } else if (strcmp(cmd, "save") == 0) {

            map_save(map);
            
        } else if (strcmp(cmd, "quit") == 0) {
            
            break;
            
        } else {

            printf("\nError: there is no such command!");
        }
    }

    free(cmd);
    free(name);

    map_clear(map);

    return 0;
}

/* Function that process name of country */
void undecorate_name(char * name)
{
    int i;

    while (name[i] != '\0') {
        if (name[i] == '_')
            name[i] = ' ';
        i++;
    }
}