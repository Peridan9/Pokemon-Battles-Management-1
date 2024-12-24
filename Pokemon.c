
#include <stdio.h>
#include "Pokemon.h"
#include <stdlib.h>
#include "Defs.h"
#include <string.h>

Type* newtype;
char* newname, newspecies;
Poke* newpoke = NULL;
Binfo* newbio;

Error_p create_pokemon(Poke **list, int counter, char* name, char* species, double height, double weight, int attack, Type *type){
	Poke* newpoke = (Poke*)malloc(sizeof(Poke));
	if(newpoke == NULL) // fail with memeory
		return MEMORY_PROBLEM;
	newpoke->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if(newpoke->name == NULL){ // fail with memory
		free(newpoke->name);
		return MEMORY_PROBLEM;
	}
	strcpy(newpoke->name,name);
	newpoke->species = (char*)malloc(sizeof(char)*(strlen(species) + 1));
	if(newpoke->species == NULL){ // fail with memory
		free(newpoke->name);
		free(newpoke);
		return MEMORY_PROBLEM;
	}
	strcpy(newpoke->species,species);
//	newpoke->species = newspecies;
	newbio = create_bioinfo_of_pokemon(weight,height,attack ); // memorycheck
	newpoke->info = newbio;
	newpoke->type = type;
	list[counter] = newpoke;
	type->numberofpokemons++;
	return SUCCESS; // we created a new pokemon :>
}



Error_p create_type_of_pokemon(Type** list, char* name, int counter){
	Type* newtype = (Type*)malloc(sizeof(Type));
	if(newtype == NULL)
		return MEMORY_PROBLEM;
	newtype->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if (newtype->name == NULL){
		free(newtype);
		return MEMORY_PROBLEM;
	}
	strcpy(newtype->name,name);
	newtype->numberofpokemons=0;
	newtype->effective_against_me = NULL;
	newtype->effective_against_others = NULL;
	newtype->othercount=0;
	newtype->mecount=0;
	list[counter] = newtype;
	return SUCCESS;
}
Type* searchtype(Type** list, char* name, int counter){
	int i = 0;
	for(i=0;i<counter;i++){
		if(strcmp(name,list[i]->name) == 0)
			return list[i];
	}
//	printf("Type name doesn't exist.");
	return NULL;
}
Poke* searchpoke(Poke** list, char* name, int counter){
	int i = 0;
	for(i=0;i<counter;i++){
		if(strcmp(name,list[i]->name)==0)
			return list[i];
	}
	return NULL;
}
Error_p add_to_effective_me(Type** list, Type *typeA, Type *typein, int counter){
	if(typeA->mecount == 0){ // empty list
		typeA->effective_against_me = (Type**)malloc(sizeof(Type*));
		if(typeA->effective_against_me == NULL)
			return MEMORY_PROBLEM;
		typeA->effective_against_me[0] = typein;
		typeA->mecount++;
		return SUCCESS;
	}
	typeA->mecount++;
	typeA->effective_against_me = (Type**)realloc(typeA->effective_against_me,(typeA->mecount)*sizeof(Type*));
	if(typeA->effective_against_me == NULL)
		return MEMORY_PROBLEM;
	typeA->effective_against_me[typeA->mecount - 1] = typein;
	return SUCCESS;
}

Error_p add_to_effective_others(Type** list, Type *typeA, Type *typein, int counter){
	if(typeA->effective_against_others == NULL){
		typeA->effective_against_others = (Type**)malloc(sizeof(Type*));
		if(typeA->effective_against_others == NULL)
			return MEMORY_PROBLEM;
		typeA->effective_against_others[0] = typein;
		typeA->othercount++;
		return SUCCESS;
	}
	typeA->othercount++;
	typeA->effective_against_others = (Type**)realloc(typeA->effective_against_others,(typeA->othercount)*sizeof(Type*));
	if(typeA->effective_against_others == NULL)
		return MEMORY_PROBLEM;
	typeA->effective_against_others[typeA->othercount - 1] = typein;
	return SUCCESS;
}

Error_p remove_from_effective_me(Type** list, Type* typeA, char *typeB, int counter){
	if(typeA->mecount == 0)
		return EMPTY_LIST;
	int i = 0;
	int place = 0;
	for(i=0;i< typeA->mecount; i++){
		if(strcmp(typeB,typeA->effective_against_me[i]->name) == 0)
			place=i;
	}
	for(i=place; i< typeA->mecount; i++){ //moving all the types need one block back
		typeA->effective_against_me[i] = typeA->effective_against_me[i+1];
	}
	typeA->mecount--;
	typeA->effective_against_me = (Type**)realloc(typeA->effective_against_me,(typeA->mecount)*sizeof(Type*));
	if(typeA->effective_against_me == NULL){
		if(place == 0)
			return EMPTY_LIST;
		return MEMORY_PROBLEM;
	}

	return SUCCESS;
}

Error_p remove_from_effective_others(Type** list, Type* typeA, char *typeB, int counter){
	if(typeA->effective_against_others == NULL)
		return EMPTY_LIST;
	int i = 0;
	int place = 0;
	for(i=0;i< typeA->othercount; i++){
		if(strcmp(typeB,typeA->effective_against_others[i]->name) == 0)
			place=i;
	}
	for(i=place; i< typeA->othercount; i++){ //moving all the types need one block back
		typeA->effective_against_others[i] = typeA->effective_against_others[i+1];
	}
	typeA->othercount--;
	typeA->effective_against_others = (Type**)realloc(typeA->effective_against_others,(typeA->othercount)*sizeof(Type*));
	if(typeA->effective_against_others == NULL){
		if(place == 0)
			return EMPTY_LIST;
		return MEMORY_PROBLEM;
	}
			// send to clear function need to add later.
	return SUCCESS;
}

Binfo* create_bioinfo_of_pokemon( double weight, double height, int attack ){
	Binfo *newbio = (Binfo*)malloc(sizeof(Binfo));
	if(newbio == NULL)
		return NULL;
	newbio->attack=attack;
	newbio->height=height;
	newbio->weight=weight;
	return newbio;

}

Error_p print_pokemon_info(Poke* poke){
	printf("%s :\n",poke->name);
	printf("%s, %s Type.\n",poke->species,poke->type->name);
	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", poke->info->height, poke->info->weight, poke->info->attack);
	return SUCCESS;
}

Error_p print_pokemon_type(Type* type){
	printf("Type %s -- %d pokemons\n", type->name, type->numberofpokemons);
	if(type->effective_against_me != NULL){ // check if there is info inside
		printf("\tThese types are super-effective against %s:%s", type->name, type->effective_against_me[0]->name);
		int i = 1;
		for(i = 1;i<type->mecount;i++){
			printf(" ,%s",type->effective_against_me[i]->name);
		}
		printf("\n");
	}
	if(type->effective_against_others != NULL){
			printf("\t%s moves are super-effective against:%s", type->name, type->effective_against_others[0]->name);
			int i = 1;
			for(i = 1;i<type->othercount;i++){
				printf(" ,%s",type->effective_against_others[i]->name);
			}
			printf("\n\n");
			return SUCCESS;
		}
	printf("\n");
	return SUCCESS;
}

Error_p clear(Type **listoftypes, Poke **listofpoke, int numtypes, int numpoke){
	int i=0;
	for(i=0;i<numtypes;i++){
		free(listoftypes[i]->effective_against_others);
		free(listoftypes[i]->effective_against_me);
		free(listoftypes[i]->name);
		free(listoftypes[i]);
	}
	int j=0;
	for(j=0;j<numpoke;j++){
		free(listofpoke[j]->species);
		free(listofpoke[j]->name);
		Error_p ccb = clearbio(listofpoke[j]->info);
		listofpoke[j]->info = NULL;
		free(listofpoke[j]);
	}
	return CLEARED;
}
Error_p clearbio(Binfo* poketoclear){
	free(poketoclear);
	return CLEARED;
}


