#ifndef _LIST_H_
#define _LIST_H_

/* Element of the list */
typedef struct _COUNTRY {
    char name[256];
    int population;
    int area;
    struct _COUNTRY * next;
} COUNTRY;

int add(COUNTRY ** list, char * name, int population, int area);
void delete(COUNTRY ** list, COUNTRY * v);
COUNTRY * find(COUNTRY * list, char * name);
void dump(COUNTRY * list);
void print_country(COUNTRY * p);
void clear(COUNTRY * list);

#endif