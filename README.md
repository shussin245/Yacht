# Yacht
A C++-programmed version of the game, Yacht!

# Table of Contents

1	Introduction to Yacht
2	Programming Approach
2.1	Game Play Overview
2.2	Dice Rolls
2.3	Scoring Categories
2.4	Single Use Categories
2.5	Points Progress
2.6	Winner Determination
2.7	Data File
3	Development Summary
3.1	Version 1
3.2	Version 2
3.3	Version 3
3.4	Version 4
3.5	Version 5
3.6	Version 6
3.7	Version 7
3.8	Version 8
4	Functions
5	Construct Utilization
6	Game Examples

# 1.   Introduction to Yacht   

Yacht is a dice game that is similar to Generala, Poker Dice, Yatzy, and Cheerio. The game is also very similar to Yahtzee, incorporating similar rules, but with a twist. The objective of the game is simple: to earn the most points. The way to earning points is by trying to make certain combinations with the five die that is given. The dice can be rolled no more than three times in a single turn to get the combinations. Once the player has agreed on a combination, he or she will choose which scoring category to use. If a player chooses a category and the combination doesn’t meet the requirements of the category, the player will earn no points for that turn. Once a category has been used, it cannot be used again by the same player in the same game, even if the player doesn’t earn points for it. Because there are 12 scoring categories, there can only be 12 rounds in a single game of Yacht.

The scoring categories for Yacht are as follows:

Category	Dice Combination	Points
Ones	Any combination	Sum of all the dice with the #1 face
Twos	Any combination	Sum of all the dice with the #2 face
Threes	Any combination	Sum of all the dice with the #3 face
Fours	Any combination	Sum of all the dice with the #4 face
Fives	Any combination	Sum of all the dice with the #5 face
Sixes	Any combination	Sum of all the dice with the #6 face
Full House	Three dice showing the same face and the other two also showing the same face	25
Four-of-a-Kind	At least four dice showing the same face	Sum of those four dice
Little Straight	1-2-3-4-5	30
Big Straight	2-3-4-5-6	30
Choice	Any combination	Sum of all the dice
Yacht	All five dice showing the same face	50

# 2.   Programming Approach

I have broken down this project into multiple steps:

1)	Initiate the dice rolls
2)	Establish the actual game play (i.e., the scoring categories)
3)	Develop a way that ensures categories aren’t used twice
4)	Enable points accumulation for each player after every round and at the end of the game
5)	Determine the winner and establish prizes
6)	Create a file that will hold the game data and winner results

# 2.1.  Game Play Overview

One game of Yacht is 12 rounds, which means that there are a total of 24 turns (12 for each player). If i%2 is true, then it’s Player 2’s turn, else, it’s Player 1’s turn.

# 2.2.  Dice Rolls

When it’s the player’s turn, he or she gets to roll the dice. If the player likes the dice that they have, they will continue. If they don’t like the combination of their dice, they have the opportunity to roll again for up to 3 times in a single turn. Every time a player rolls their dice, a point is added to ag_pts. When ag_pts is greater than 3, the player won’t be allowed to roll their dice again and their turn will continue as usual.
 
# 2.3.  Scoring Categories

Once a proper scoring category has been chosen, the program will do the calculations depending on the scoring category that was used:

# 2.4.  Single Use Categories

As mentioned before, each category is to be only used once by the same player for each game. The way that I made sure that was is the case is to add a point inside the statements of the scoring category calculations. Since I initialized them with 0, an addition of 1 will indicate to the program that the scoring category has already been used. When the player has a later turn and enters a scoring category into scoCat that has already been used, the program will prompt the player to enter a different category. For example, let’s say that at the beginning of the game, Player 1 used the category “Ones”. If Player 1 tries to use that category again, the program will not allow it because a point has been added to o2.

# 2.5.  Points Progress

After every turn, the total points accumulated for each player will be displaced. These points will again be displayed once the game is finished in order to determine the winner.

# 2.6.  Winner Determination

Upon completion of the 12 rounds, the total points for each player will be compared in order to determine the winner of the game. Additionally, each winner will have the opportunity to get a prize from the mystery box.

# 2.7.  Data File

The player’s names, the points for each player after every turn, and the final points for each player asl well as the winner were all data that will be saved into a data file.

# 3.   Development Summary

# 3.1.  Version 1

In Version 1, I defined and initialized most of the variables. I also. completed the dice rolls for each player. Additionally, I completed the code for the scoring categories, “Ones”, “Twos”, “Threes”, “Fours”, “Fives”, “Sixes”, and “Four-of-a-Kind”. In this version, I only started code for one of the players, not both. The reason why is to make it easier to transfer good code to the other player once I have completed all the code.

# 3.2.  Version 2

In Version 2, I finished all the scoring categories, which includes “Full House”, “Little Straight”, “Big Straight”, “Choice”, and “Yacht”. Version 2 is also where I finished the code for determining which categories were already used.

# 3.3.  Version 3

Version 3 is where I figured out how to allow players to roll their dice up to 3x in a single turn. It’s also where I completed all the game play and was able to transfer it to the other player.

# 3.4.  Version 4

Beginning Version 4, it was mostly modifications and miscellaneous additions. In this Version, specifically, I included the ability for players to view the total points after every turn and once again at the end of the game. I also determined the winner in the version and included a mystery box prize for the winner in order to use other constructs needed for this particular project.

# 3.5.  Version 5

Version 5 is where I added more comments throughout my code and formatted my code to look clean. It’s also where I created a file to store all the necessary data mentioned before.

# 3.6.  Version 6

In Version 6, I began to create functions that will be useful throughout my code. I first began by creating a bool function that determines the winner. Other functions allowed for better formatting of the game.

# 3.7.  Version 7

Version 7 is where I placed the dice combinations from every turn for each player into a single dimensional array. This allowed me to work with the array and validate the scoring categories more easily. More notably, I’m able to sort the dice combination so it’s able to better validate for the “Little Straight” and “Big Straight” categories. One of the functions that will be discussed later will be used to validate scoring categories from “Ones” to “Sixes”. Earlier, I would depend on the used to tell the program how many dice with the face #1 they had, but in this version, I created a function that determines if there is a #1 die and, if there is, how many times is it repeated in the array (the dice roll). The same idea is iterated from up to the “Sixes” category.

# 3.8.  Version 8

I finalized my code in Version 8. When I was playing the game, I noticed that I kept forgetting which categories I have used and which I haven’t, so I created a function that allowed me to enter “v” when asked for a scoring category and it will show me which categories I have and haven’t used. I also edited the way prizes were selected for the winner. From Project 1, I made a mistake which didn’t show the prize selected correctly. In this version, I created a function for the prizes. Finally, I created a function that validates the ”Four-of-a-Kind” category.

# 4.   Functions

Function	Arguments	Use
Int points	Float pts	Returns an integer with the total points for each player at the end of the round
Bool win	Float pts1, float pts2	Determines the winner of the game by comparing the points of both players
Void sep1	String &name1, string &name2, int length	Creates a separation when displaying certain information to make the text neater
Void sep2	String &name1, string &name2, float length	Creates a separation when displaying certain information to make the text neater
Void sep	Int length	Creates a separation when displaying certain information to make the text neater
Void sep	Int length 1, int length2	Creates a separation when displaying certain information to make the text neater
Int val1	Int array[], int SIZE	Validates categories “Ones” to “Sixes” by returning the number of times that number is repeated, if found
Void bubSort	Int array[], int SIZE	Sorts the dice combination for Player 2
Void disAry	Int array[], int SIZE	Displays an array with the player’s dice combination
Void selSort	Int array[], int SIZE	Sorts the dice combination for Player 1
Bool binSrch	Int array[], int SIZE, int num	Makes sure that the number for categories “Ones” to “Sixes” is actually within the dice combination of the player
Void prtAry	String array[3][4]	Prints the array filled with the categories that have and haven’t been used by the player throughout the game
Void cntDown	Vector<int> vect	A vector that displays its contents as a countdown when the players begin the game
Void prize	Int num	A function containing a switch statement that allows the user to pick their prize
Int repeat	Int array[], int SIZE	Returns a value that shows how many times a particular number was repeated in an array; helpful for categories “Ones” to “Sixes” and “Four-of-a-Kind”
