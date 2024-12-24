/*
 * MainFirst.c
 *
 *  Created on: Nov 24, 2021
 *      Author: ise
 */
#include "Pokemon.h"

int main(int argc, char **argv){
	int numberofpokemons = atoi(argv[2]);
	int numberoftypes = atoi(argv[1]);
	int types_counter = 0;
	int pokemons_counter = 0;
	Type **listoftypes = (Type**)malloc(numberoftypes*sizeof(Type*)); // add memory check?
	Poke **listofpokemons = (Poke**)malloc(numberofpokemons*sizeof(Poke*));


	FILE *text = fopen(argv[3], "r");
	char line[300];
	char *readline;
	char *token;
	int getypes=0;
	int getpoke=0;
	while(fgets(line,300,text)){
		readline = strtok(line,"\n\r");
		if(readline == NULL)
					break;
		if(strcmp(readline,"Types")==0){
			getypes=1;
			continue;
		}
		if(strcmp(readline,"Pokemons") == 0 && getypes == 1)
			break;
		if(getypes == 1){
			token = strtok(readline, ",");
			while(token != NULL){
				Error_p newtype = create_type_of_pokemon(listoftypes, token, types_counter);
				if(newtype == 1){
					Error_p clean = clear(listoftypes, listofpokemons, numberoftypes, numberofpokemons); // memory check
					printf("Memory Probelm");
					return 1;
				}
//				if(newtype)
				types_counter++;
				token = strtok(NULL, ",");
			}
			getypes=0;
			continue;
		}
		if(readline[0] == '\t'){
			readline++;
			token = strtok(readline, " ");
			Type* typeA = searchtype(listoftypes, token, types_counter); // no need for memory check
			while(token != NULL){
				token = strtok(NULL, ":");
				if(strcmp(token,"effective-against-me") == 0){
					token = strtok(NULL, ",");
					while(token != NULL){
						Type * typein = searchtype(listoftypes, token, types_counter);
						Error_p newme = add_to_effective_me(listoftypes, typeA, typein, types_counter);
						if(newme == 1){
							clear(listoftypes, listofpokemons, numberoftypes, numberofpokemons); // memory check
							printf("Memory Problem");
							return 1;
						}
						token = strtok(NULL, ",");
					}
					break;
				}
				if(strcmp(token,"effective-against-other") == 0){
					token = strtok(NULL, ",");
					while(token != NULL){
						Type * typein = searchtype(listoftypes, token, types_counter);
						Error_p newother = add_to_effective_others(listoftypes, typeA, typein, types_counter);
						if(newother == 1){
							clear(listoftypes, listofpokemons, numberoftypes, numberofpokemons); // memory check
							printf("Memory Problem");
							return 1;
						}
						token = strtok(NULL, ",");
					}
					break;
				}
			}
			continue;
		}
		if(strcmp(readline,"Pokemons") == 0){
			getpoke=1;
			continue;
		}
		if(getpoke == 1){
			token = strtok(readline, ",");
			char* pokename = token;
			token = strtok(NULL, ",");
			char* pokespecies = token;
			token = strtok(NULL, ",");
			double pokeheight = atof(token);
			token = strtok(NULL, ",");
			double pokeweight = atof(token);
			token = strtok(NULL, ",");
			int pokeattack = atoi(token);
			token = strtok(NULL, ",");
			Type* pointer = searchtype(listoftypes, token, types_counter);
			Error_p newpoke = create_pokemon(listofpokemons, pokemons_counter, pokename, pokespecies, pokeheight, pokeweight, pokeattack, pointer);
			if(newpoke == 1){
				clear(listoftypes, listofpokemons, numberoftypes, numberofpokemons); // memory check
				printf("Memory Problem");
				return 1;
			}
			pokemons_counter++;
			continue;
		}
	}
	fclose(text);

	char choise = 1;
	int i = 0;
	char typeAstr[300];
	char typeBstr[300];
	char poke[300];
	char type[300];


	while(1)
	{
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons\n");
		printf("2 : Print all Pokemons types\n");
		printf("3 : Add type to effective against me list\n");
		printf("4 : Add type to effective against others list\n");
		printf("5 : Remove type from effective against me list\n");
		printf("6 : Remove type from effective against others list\n");
		printf("7 : Print Pokemon by name\n");
		printf("8 : Print Pokemons by type\n");
		printf("9 : Exit\n");
		scanf(" %c", &choise); // change to char
		getchar();
		Type* typeA = NULL;
		Type* typeB = NULL;

		switch(choise)
		{
		case '1':
			for(i=0;i<numberofpokemons;i++){
				Error_p printpokemons = print_pokemon_info(listofpokemons[i]); // no need to check memory
			}
			i = 0;
			break;

		case '2':
			for(i=0;i<numberoftypes;i++){
				Error_p printtypes = print_pokemon_type(listoftypes[i]); // no need to check memory

			}
			i = 0;
			break;

		case '3':
			printf("Please enter type name:\n");
			scanf("%s", typeAstr);
			Type* typeA = searchtype(listoftypes, typeAstr, types_counter);
			if(typeA == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			printf("Please enter type name to add to %s effective against me list:\n", typeA->name);
			scanf("%s", typeBstr);
			Type* typeB = searchtype(listoftypes, typeBstr, types_counter);
			if(typeB == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			Type* typecheck = searchtype(typeA->effective_against_me, typeB->name, typeA->mecount);
			if(typecheck != NULL){
				printf("This type already exist in the list.\n");
				break;
			}
			Error_p newme = add_to_effective_me(listoftypes, typeA, typeB, types_counter);
			if(newme == 1){ // memory check
				printf("Memory Problem");
				clear(listoftypes, listofpokemons, numberoftypes, numberofpokemons);
				return 1;
			}
			Error_p printtypes = print_pokemon_type(typeA);

			break;

		case '4':
			printf("Please enter type name:\n");
			scanf("%s", typeAstr);
			typeA = searchtype(listoftypes, typeAstr, types_counter);
			if(typeA == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			printf("Please enter type name to add to %s effective against others list:\n", typeA->name);
			scanf("%s", typeBstr);
			typeB = searchtype(listoftypes, typeBstr, types_counter);
			if(typeB == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			typecheck = searchtype(typeA->effective_against_others, typeB->name, typeA->othercount);
			if(typecheck != NULL){
				printf("This type already exist in the list.\n");
				break;
			}
			Error_p newothers = add_to_effective_others(listoftypes, typeA, typeB, types_counter);
			if(newothers == 1){ // memory check
				printf("Memory Problem");
				clear(listoftypes, listofpokemons, numberoftypes, numberofpokemons);
				return 1;
			}
			printtypes = print_pokemon_type(typeA);

			break;

		case '5':
			printf("Please enter type name:\n");
			scanf("%s",typeAstr);
			typeA = searchtype(listoftypes, typeAstr, types_counter);
			if(typeA == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			printf("Please enter type name to remove from %s effective against me list:\n", typeA->name);
			scanf("%s",typeBstr);
			typeB = searchtype(typeA->effective_against_me, typeBstr, typeA->mecount);
			if(typeB == NULL){
				printf("Type name doesn't exist in the list.\n");
				break;
			}
			Error_p removeme = remove_from_effective_me(listoftypes, typeA, typeBstr, types_counter);
			if(removeme == 1){ // memory check
				printf("Memory Problem");
				clear(listoftypes, listofpokemons, numberoftypes, numberofpokemons);
				return 1;
			}
			printtypes = print_pokemon_type(typeA);
			break;

		case '6':
			printf("Please enter type name:\n");
			scanf("%s",typeAstr);
			typeA = searchtype(listoftypes, typeAstr, types_counter);
			if(typeA == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			printf("Please enter type name to remove from %s effective against others list:\n", typeA->name);
			scanf("%s",typeBstr);
			typeB = searchtype(typeA->effective_against_others, typeBstr, typeA->othercount);
			if(typeB == NULL){
				printf("Type name doesn't exist in the list.\n");
				break;
			}
			Error_p removeothers = remove_from_effective_others(listoftypes, typeA, typeBstr, types_counter);
			if(removeothers == 1){ // memory check
				printf("Memory Problem");
				clear(listoftypes, listofpokemons, numberoftypes, numberofpokemons);
				return 1;
			}
			printtypes = print_pokemon_type(typeA);
			break;

		case '7':
			printf("Please enter Pokemon name:\n");
			scanf("%s", poke);
			Poke* poketoprint = searchpoke(listofpokemons, poke, pokemons_counter);
			if(poketoprint == NULL){
				printf("The Pokemon doesn't exist.\n");
				break;
			}
			Error_p print = print_pokemon_info(poketoprint);
			break;

		case '8':
			printf("Please enter type name:\n");
			scanf("%s", type);
			Type* typetoprint = searchtype(listoftypes, type, types_counter);
			if(typetoprint == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			if(typetoprint->numberofpokemons == 0){
				printf("There are no Pokemons with this type.\n");
				break;
			}
			printf("There are %d Pokemons with this type:\n", typetoprint->numberofpokemons);
			for(i=0;i<numberofpokemons;i++){
				if(listofpokemons[i]->type == typetoprint)
					print = print_pokemon_info(listofpokemons[i]);
			}
			break;

		case '9': ;
			Error_p clean = clear(listoftypes, listofpokemons, numberoftypes, numberofpokemons);
			free(listofpokemons);
			free(listoftypes);
			printf("All the memory cleaned and the program is safely closed.\n");
			exit(0);

		default:
			printf("Please choose a valid number.\n");
		}
	}
	return 1;
}
