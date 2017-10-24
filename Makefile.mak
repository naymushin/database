country: country.o list.o map.o
        gcc country.o list.o map.o -o country
country.o: country.c
        gcc -c country.c
list.o: list.c
        gcc -c list.c
map.o: map.c
        gcc -c map.c
clean:
        rm country.o list.o map.o country country_list