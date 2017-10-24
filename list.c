#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/* Defines type of pointer to the function that compares two elements of list */
typedef int (* CMP_FUNC)(COUNTRY * v1, COUNTRY * v2);

/*
 * Allocates memory for the new element of list,
 * initializes fields and adds element to the head of list.
 * Changes pointer to the head of list. Returns 0 if new element was successfully
 * added or 1 if it was impossimble to allocate memory for element. 
 */
int add(COUNTRY ** list, char * name, int population, int area) {

    COUNTRY * line = (COUNTRY *)malloc(sizeof(COUNTRY));

    if (line) {

        strcpy(line->name, name); 
        line->population = population; 
        line->area = area;
        line->next = *list;
        *list = line;

        return 0;
    } 

    return 1;
}

/*
 * Deletes element of list and frees its memory.
 * If element was first in the list, changes pointer to the list 
 */
void delete(COUNTRY ** list, COUNTRY * v) {

    COUNTRY * p = *list;
    COUNTRY * prev = NULL;

    while (p != NULL) {

        if (p == v) {

            if (prev)
                prev->next = p->next;            
            else 
                *list = p->next;
    
            free(p);

            break;
        }

        prev = p;
        p = p->next;
    }
}

/*
 * Performs seacrh in the list for country using its name. Returns pointer to found
 * element or NULL, if country with such name doesn't exist in list.
 */
COUNTRY * find(COUNTRY * list, char * name) {

    COUNTRY * p = list;
    
    while(p != NULL) {
    
        if(strcmp(p->name, name) == 0)
            break;
        else
            p = p->next;        
    }

    return p;
}

/* Function for printing information about country from the list */
void print_country(COUNTRY * p) {

    printf("%s, ", p->name);

    if(p->population == 0)
        printf("unknown, ");
    else
        printf("%d, ", p->population);
    if(p->area == 0)
        printf("unknown\n");
    else
        printf("%d\n", p->area);
}

/* Function for printing information about all countries in the list */
void dump(COUNTRY * list) {

    COUNTRY * p = list;

    while (p != NULL) {

        print_country(p);
        p = p->next;
    
    }
}

/* Function that deletes first country of the list */
void clear(COUNTRY * list) {

    while(list != NULL) {

        COUNTRY * p = list;
        delete(&list, p);
    }
}