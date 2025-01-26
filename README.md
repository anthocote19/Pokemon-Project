# Supémon CLI Game

## 1. Introduction 
**SUPINFO World CLI Gaming** asks you to develop a console (CLI) version of Pokémon in C, called **Supémon**.  

### Project Details
- **Groups:** Maximum of 2 students (1 group of 3 allowed if the class has an odd number of students).
- **Duration:** 3 weeks.
- **Rules:**
  - Copying or adapting existing code is strictly prohibited.
  - Sharing information between groups is not allowed.
  - Any rule violation will result in a grade of **0**.

For more details about the Pokémon concept, visit this [link](https://www.pokemon.com).

---

## 2. Implementations

### 2.1. Program Launch
- Allow the player to:
  - Enter a name.
  - Choose a starting Supémon.
- Load a backup file if available.

### 2.2. Out-of-Combat Actions
1. **Into the Wild:** Launch a fight against a random Supémon.
2. **Shop:** Allows the player to buy or sell items:
   - **Buying mode:** Display all available items with their descriptions and prices. Allow the player to purchase a specific item.
   - **Selling mode:** Display all items owned by the player with their selling prices. Allow the player to sell a specific item.
3. **Supémon Center:** Display all player’s Supémons and offer to heal them (free of charge).
4. **Leave the Game:** Exit the game, with or without saving progress.

### 2.3. Player
The player has:
- A name.
- A list of Supémons.
- A selected Supémon (for battles).
- Supcoins (used to buy items).
- A list of items.

### 2.4. Supémons
Supémons have:
- A name.
- Level (starting at 1).
- Experience (starting at 0).
- HP and Max HP (current and maximum health points).
- Attack and Base Attack (current and base attack power).
- Defense and Base Defense (current and base defense power).
- Evasion and Base Evasion (chance to dodge attacks).
- Accuracy and Base Accuracy (chance to hit an opponent).
- Speed (determines turn order).
- A list of moves.

#### Supémons to Implement (Level 1 Stats):
1. **Supmander:**
   - HP: 10
   - Attack: 1
   - Defense: 1
   - Evasion: 1
   - Accuracy: 2
   - Speed: 1
   - Moves:
     - Scratch (deals 3 damage)
     - Grawl (increases Attack by 1)

2. **Supasaur:**
   - HP: 9
   - Attack: 1
   - Defense: 1
   - Evasion: 3
   - Accuracy: 2
   - Speed: 2
   - Moves:
     - Pound (deals 2 damage)
     - Foliage (increases Evasion by 1)

3. **Supirtle:**
   - HP: 11
   - Attack: 1
   - Defense: 2
   - Evasion: 2
   - Accuracy: 1
   - Speed: 2
   - Moves:
     - Pound (deals 2 damage)
     - Shell (increases Defense by 1)

#### Move Mechanics:
- **Damage Formula:**  
  `Launcher_Attack x Damage / Target_Defense`  
  If the result is not an integer, round up or down randomly.
- **Dodge Formula:**  
  `Launcher_Accuracy / (Launcher_Accuracy + Target_Evasion) + 0.1`  
  Example: `2 / (2 + 2) + 0.1 = 60% success rate`.

### 2.5. Battle
When entering the wild, initiate a turn-based battle against a random Supémon:
- The wild Supémon's level matches the player's selected Supémon.
- **Turn Order:** Determined by Speed (random if tied).
- **Player Actions:**
  1. **Move:** Choose one move from the selected Supémon’s list.
  2. **Change Supémon:** Switch to another Supémon (skips the turn).
  3. **Use Item:** Apply an item to a Supémon (max 4 items per battle).
  4. **Run Away:** Attempt to flee using  
     `Player_Speed / (Player_Speed + Enemy_Speed)` success rate.
  5. **Capture:** Attempt to capture the enemy Supémon using  
     `(Enemy_MaxHP - Enemy_HP) / Enemy_MaxHP - 0.5` success rate.

- **Enemy Actions:** Randomly choose an attack from its move pool.
- **Battle End Conditions:**
  - A Supémon’s HP reaches 0 or less.
  - **Victory:** Earn 100–500 Supcoins and experience (100–500 × enemy level).
  - **Defeat:** No rewards.

### 2.6. Items
Implement at least the following items in the shop:
1. **Potion:** +5 HP (100 Supcoins).
2. **Super Potion:** +10 HP (300 Supcoins).
3. **Rare Candy:** Adds 1 level to a Supémon (700 Supcoins).  
   **Selling Price:** Purchase price divided by 2.

### 2.7. Experience and Level
- Supémons gain levels but do not evolve.
- **Level-Up:** Increases all stats by 30%.  
  Round up or down randomly for non-integer values.
- **Experience Requirements:**  
  - Level 2: 500 points.  
  - Each subsequent level requires 1,000 additional points.

### 2.8. Save System
Implement a backup file that saves the player’s:
- Name.
- Supémon list (and their stats).
- Items.
- Supcoins.
