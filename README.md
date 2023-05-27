# projet-info : Memory-RPG
Use 'make' to compile and then './exec.exe' to execute the game.  
The menu opens.  
Input 'p' to play, 'r' to check the rankings, 'c' to close the game.   
The rankings are sorted by wins, then by treasures found, then by monsters killed and finally by tiles revealed.
When checking the rankings, input anything to go back to the menu.  
Input 'n' to start a new game, 'm' to go back to the menu.  
When beginning a new game, choose the number of players and select a username for each.   
Create your characters, manually (select a class and a color) or not.   
Each player will play a turn until one wins, starting from their spawn until their character dies, becomes stuck or wins.  
A turn consists of:  
- selecting a side to go to;
- choosing a weapon;  
- revealing a tile and acting accordingly:
   - if the tile is a monster, the player will die or defeat it depending on their selected weapon.   
      - the basilics will kill the player if he doesn't wield a shield   
      - the trolls will kill the player if he doesn't wield an axe
      - the zombies will kill the player if he doesn't wield a torch
      - the harpies will kill the player if he doesn't wield a bow
   - if the tile is an artifact, the player will collect or leave it depending on their selected class.   
   - if the tile is a treasure chest, the player will collect it and move on.   
   - if the tile is a totem, the player will have to enter two numbers corresponding to the line and column of the totem's new location before dying.   
   - if the tile is a portal, the player will have to enter two numbers corresponding to the line and column of their new location before skipping the movement and repeating the actions listed above at their new location. 

- moving on or going back to the spawn:  
   - moving on means selecting an adjacent hidden tile with zqsd controls for the player's character new position.  
   - going back to the spawn is triggered by the character's death or being stuck (having no available adjacent tiles). It triggers the end of the turn. 
  
The first action of a turn, the player moves automatically onto the spot next to their spawn, so they don't select a side until their turn's second action. 
This repeats until the turn ends.  
The game ends when one player discovers both their class' artifact and at least one chest in the same turn.  
At the end of the game, two inputs are asked for some reason.
All along the game, inputs will be required to move onto the next action, screen or turn.  
Inputs for specific data will repeat with an appropriate error message until valid data is provided .   
The map's display may be staggered in some places due to printing issues.  
Once the game ends, restart with the same parameters with 'r' or return to the menu.   
 





