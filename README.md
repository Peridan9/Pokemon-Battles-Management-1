# 🐾 Pokémon Battle System 🧪

This project was developed as part of my **Advanced Programming** course at Ben-Gurion University. It implements a **Pokédex** and **Pokémon battle system**, focusing on memory management and dynamic structures in **C**. The system allows users to manage Pokémon data, simulate battles, and navigate an interactive menu.

---

## ✨ Features

- 📜 **Pokédex System:** Create and manage a Pokédex with dynamic Pokémon types and data.
- ⚔️ **Battle Simulation:** Handle Pokémon battles with type effectiveness and attributes.
- 📂 **Configuration Support:** Load Pokémon and type data from a configuration file.
- 🛠️ **Dynamic Memory Management:** Efficient memory usage with proper allocation and cleanup.
- 📊 **Interactive Menu:** User-friendly interface to manage Pokémon, types, and battle interactions.

---

## ⚙️ Prerequisites

To run this project, ensure you have the following installed:

- ✅ GCC or any compatible C compiler
- ✅ Valgrind for memory leak testing

---

## 🖍️ Usage Instructions

1. Compile the project using the provided `makefile`:

   ```bash
   make
2. Run the program with the required arguments:
     ```bash
      ./Pokedex <numberOfTypes> <numberOfPokemons> <configurationFile>
     ```
   - `<numberOfTypes>:` Total Pokémon types to load.

   - `<numberOfPokemons>:` Total Pokémon to load.

   - `<configurationFile>:` Path to the configuration file.

3. Interact with the main menu to explore the system:
    - View Pokémon and type details.
    - Add or remove effectiveness between types.
    - Print specific Pokémon or type data.
    - Exit safely with memory cleanup.

---
## 🛠 File Structure
- Pokemon.h: Contains struct definitions and function declarations.
- Pokemon.c: Implements Pokémon and type functionalities.
- MainFirst.c: Main program logic and menu system.
- Defs.h: General definitions and enums for the project.

---
## 🤾 Example Configuration File

```bash
Types  
Fire,Water,Electric,Grass  

Fire effective-against-me:Water  
Fire effective-against-other:Grass,Electric  
Electric effective-against-other:Water  

Pokemons  
Pikachu,MousePokemon,0.4,6,55,Electric  
Charmander,LizardPokemon,0.6,8.5,52,Fire  
Ponyta,FireHorsePokemon,1.0,30.0,85,Fire  
Squirtle,TinyTurtlePokemon,0.5,9,48,Water  
Psyduck,DuckPokemon,0.8,19.6,52,Water
```
---
## 🔍 Additional Notes
- Ensure memory leaks are resolved using tools like Valgrind.
- Follow the provided menu options strictly to maintain proper functionality.
- Refer to the project documentation for detailed implementation details.
Feel free to explore, modify, and enhance the project! 🚀
