
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct Type
{
	char *name;
	int numberofpokemons; // number of pokemons of the type
	struct Type** effective_against_others;
	struct Type** effective_against_me;
	int othercount; // number of types in others
	int mecount; // number of types in me

}Type;

typedef struct BioInfo
{
	double height;
	double weight;
	int attack;
}Binfo;

typedef struct Pokemon
{
	char *name; /* check what is the limit ?*/
	char *species;
	struct Type* type;
	struct BioInfo* info;
}Poke;

Error_p create_pokemon(Poke **list, int counter, char* name, char* species, double height, double weight, int attack, Type *type);
Error_p create_type_of_pokemon(Type** list, char* name, int counter);
Binfo* create_bioinfo_of_pokemon( double weight, double height, int attack );
Error_p add_to_effective_me(Type** list, Type *typeA, Type *typein, int counter);
Error_p add_to_effective_others(Type** list, Type *typeA, Type *typein, int counter);
Type* searchtype(Type** list, char* name, int counter);
Error_p remove_from_effective_me(Type** list, Type* typeA, char *typeB, int counter);
Error_p remove_from_effective_others(Type** list, Type* typeA, char *typeB, int counter);
Error_p print_pokemon_info(Poke* poke);
Error_p print_pokemon_type(Type* type);
Error_p clear(Type **listoftypes, Poke **listofpoke, int numtypes, int numpoke);
Poke* searchpoke(Poke** list, char* name, int counter);
Error_p clearbio(Binfo* poketoclear);



