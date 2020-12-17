# Tournament-AI
Final project for intro to AI course using  reinforcement learning

Using reinforcement learning with Q-Learning with Function Approximation an AI was created that must learn over time to defeat 3 types of other AIs each with a unique style of play. 
The rules were as follows
The default setting is 5 rounds of practice (where score does not count), and 20 rounds of combat.
In each round, each character starts with 100 points of health. A round is finished when one character's health reaches 0.
Each round consists of many turns. In each turn, each character chooses one of the available actions, and both of them perform their chosen actions at the same time.
There are 8 actions available in general.
0 Cast Magic Missile - dealing 7 points of magic damage to the opponent.
1 Cast Fireball - dealing 14 points of magic damage to the opponent, but will randomly miss the opponent 33% of the time, causing no damage.
2 Attack with a dagger - dealing 7 points of physical damage.
3 Attack with a staff - dealing 9 points of physical damage, but may give the opponent an attack of opportunity 33% of the time, and lose half of the damage dealt as damage to yourself.
4 Cast Globe of Invulnerability - starting from the turn it is cast, for 6 turns, fully negates all magic damage.
5 Cast Stoneskin - starting from the turn it is cast, for 6 turns, fully negates all physical damage (from dagger/staff).
6 Cast Strength of Might - starting from the turn after it is cast, for 6 turns, all physical attacks deal double damage, and your fireball has enough strength to blast through a Globe of Invulnerability, dealing normal fireball damage.
7 Drink a healing potion - instantly gets back 50 points of health (max 100). You have only one healing potion per round. Use it wisely

The project is run in an tournament application and was eventually used to play against other clasemates in a tournament. 
