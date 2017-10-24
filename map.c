#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "map.h"

#define DBNAME "country_list"
#define MAP_SIZE 64
#define MAX_LINE_LENGTH 255

/* Function that returns hash of the key.
Key is name of the country. */
unsigned int hash(char * key) {

    unsigned int i, h = 0;

    for(i = 0; i < strlen(key); i++)
        h += key[i];

    return h % MAP_SIZE;
}

/* Function that returns element to the hash-table */
void map_add(COUNTRY ** map, char * name, int population, int area) {

    unsigned int h = hash(name);

    COUNTRY *v = find(map[h], name);

    if(v != NULL) {

        v->population = population;
        v->area = area;

    } else {

        if(add(&map[h], name, population, area) == 1)            
            printf("\nAn error occurred while memory allocation!\n");                   
    }
}

/* Function that deletes country with specified name from the hash-table */
void map_delete(COUNTRY ** map, char * name) {

    unsigned int h = hash(name);

    COUNTRY *v = find(map[h], name);
    
    if(v != NULL)
        delete(&map[h], v);
    else
        printf("\nThere is no such country!\n");
}

/* Function that perfroms search of country with specified name in the hash-table */
COUNTRY * map_find(COUNTRY ** map, char * name) {

    unsigned int h = hash(name);

    COUNTRY *v = map[h];
    
    return find(v, name);
}

/* Function that prints all entries of hash-table on the screen */
void map_dump(COUNTRY ** map) {

    int i;

    for (i = 0; i < MAP_SIZE; i++)
        dump(map[i]);
}

/* Function that prints one entry from hash-table on the screen */
void map_view(COUNTRY ** map, char * name) {

    unsigned int h = hash(name);

    COUNTRY *v = find(map[h], name);

    if(v != NULL)
        print_country(v);
    else
        printf("\nThere is no such country!\n");        
}

/* Function that creates hash-table */
COUNTRY ** map_create(void) {

    COUNTRY ** map = (COUNTRY **)calloc(MAP_SIZE, sizeof(COUNTRY *));
    return map;
}

/* Function that deletes hash-table */
void map_clear(COUNTRY ** map) {

    int i;

    for (i = 0; i < MAP_SIZE; i++)
        clear(map[i]);

    free(map);
}

/* Function that loads hash-table from file */
COUNTRY ** map_load() {

    char buf[MAX_LINE_LENGTH + 1], *parameters[3];
    int i, par_number;
    COUNTRY ** map = NULL;

    FILE * f = fopen(DBNAME, "r");

    map = map_create();

    buf[MAX_LINE_LENGTH] = '\0'; 
 
    if (f) {
        
        while(fgets(buf, MAX_LINE_LENGTH, f)) {

            par_number = 0;
            parameters[par_number++] = buf;
            i = 0;

            while(buf[i]) {

                if (buf[i] == ',') {

                    buf[i] = '\0';
                    parameters[par_number++] = &buf[i + 1];

                }

                i++;
            }

            if (par_number == 3)
                map_add(map, parameters[0], atoi(parameters[1]), atoi(parameters[2])); 
            
        }

        fclose(f);
    }
    
    return map;
}

/* Function that saves hash-table to the file */
void map_save(COUNTRY ** map) {
   
    int i;

    COUNTRY * v;   

    FILE * f = fopen(DBNAME, "w");

    if (f) {

        for (i = 0; i < MAP_SIZE; i++) {

            v = map[i];

            while (v != NULL) {

                fprintf(f, "%s,%d,%d\n", v->name, v->population, v->area);
                v = v->next;
            }
        }

        fclose(f);
    }
}