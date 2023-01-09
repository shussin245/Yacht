/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Yacht - Version 8                                                           *
 * 1. Allowed players to view which categories they've used and which they     *
 * left anytime throughout the game.                                           *
 * 2. Edited the way prizes are selected by including the switch case into a   *
 * function and including exit(0) statements.                                  *
 * 3. Created validation for Four-of-a-Kind                                    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//System Libraries
#include <iostream>     //Needed for general coding
#include <cstdlib>      //Needed for random # generator
#include <ctime>        //Needed for random # generator
#include <iomanip>      //Needed for calculating points
#include <cstring>      //Needed for a lot of names, categories, & prizes
#include <cmath>        //Needed to periodically show points
#include <fstream>      //Needed to collect data into a single file
#include <vector>       //Needed for creating and working with vectors
using namespace std;

//User Libraries

//Global Constants
const int MAX_NUM = 6;  //Max # for a die is 6
const int MIN_NUM = 1;  //Min # for a die is 1
const int SIZE = 5;     //size of the 1D arrays (dice combinations)

//Function Prototypes
int points(float);       //shows the total points for each player at the end of a round
bool win(float, float);  //determines the winner of the game
void sep1(string &, string &, int length = 43); //Created a separation when displaying
                                                //certain things to make the text neater
void sep2(string &, string &, float length = 15);
void sep(int);
void sep(int, int);
void bubSort(int [], int);      //sorting the dice in ascending order (player 2)
void selSort(int [], int);      //sorting the dice in ascending order (player 1)
void disAry(int [], int);       //displaying the player their array
bool binSrch(int [], int , int);//Makes sure that there's a number matching the
                                //requirements needed for categories "ones" to "sixes"
int val1(int [], int, int);     //validation for categories "ones" to "sixes"
int repeat(int [], int);        //validation for category "Four of a Kind"
void prtAry(string [3][4]);     //Displays 2D array of categories used
void cntDown(vector<int>);      //displays countdown to begin the gam
void prize(int);                //Displays the winner's prize 

//Main Function
int main(int argc, char** argv) 
{
//SYSTEM TIME AND RANDOM NUMBER GENERATOR
    
    unsigned seed = time(0);
    srand(seed);
    
//TITLE
    
    sep(28);
    cout<<"Welcome to the Game of Yacht!"<<endl;
    sep(14, 2);
    cout<<endl;
    
//DECLARING VARIABLES
    
    fstream game; //outputting all round results and final results into a file
    string name1, name2;                        //names of players
    int dice11, dice12, dice13, dice14, dice15; //dice for player 1
    int dice21, dice22, dice23, dice24, dice25; //dice for player 2
    char again;               //players can roll their dice up to 3x in a turn
    int ag_pts;               //Determining how many times they rolled their die
    char rules;               //Viewing of rules
    string scoCat;            //scoring category to use
    float points1, points2;   //total points for both players
    int o2 = 0;  //once a category is used by one player, it cannot be used again by the
    int t2 = 0;  //same player; these variables represent the different category available
    int tr2 = 0; //for use by each player; once a category is used, a point will be added,
    int f2 = 0;  //indicating to the program that the category is already used
    int fv2 = 0;
    int s2 = 0;
    int fh2 = 0;
    int k2 = 0;
    int ls2 = 0;
    int bs2 = 0;
    int c2 = 0;
    int y2 = 0;
    int o1 = 0;
    int t1 = 0;
    int tr1 = 0;
    int f1 = 0;
    int fv1 = 0;
    int s1 = 0;
    int fh1 = 0;
    int k1 = 0;
    int ls1 = 0;
    int bs1 = 0;
    int c1 = 0;
    int y1 = 0;
    int myst;   //winner's choice in mystery box prize
    string used1[3][4] = {{"Ones", "Twos", "Threes", "Fours"},
                            {"Fives", "Sixes", "Full House", "Four-of-a-Kind"},
                            {"Little Straight", "Big Straight", "Choice", "Yacht"}};
    string used2[3][4] = {{"Ones", "Twos", "Threes", "Fours"},
                            {"Fives", "Sixes", "Full House", "Four-of-a-Kind"},
                            {"Little Straight", "Big Straight", "Choice", "Yacht"}};
    vector<int> begin(3);   //countdown to begin the game
    begin[0] = 3;
    begin[1] = 2;
    begin[2] = 1;
    
//OPENING FILE
    
    game.open("results.dat",ios::out);
    
//PLAYER NAMES
    
    cout<<"What is Player 1's name?"<<endl; 
    cin>>name1;
    cout<<"What is Player 2's name?"<<endl;
    cin>>name2;
    
//OUTPUTTING PLAYER NAMES TO A FILE
    
    game<<"Player 1: "<<name1<<endl;
    game<<"Player 2: "<<name2<<endl;
    game<<endl;
    
//PLAYERS CAN VIEW THE RULES OF THE GAME BEFORE STARTING
    
    cout<<"Before we begin, would you like to review the rules of the game? (y/n)"<<endl;
    cin>>rules;
    if (rules == 'y')
    {
        cout<<"Yacht is a dice game consisting of 12 rounds played by at least 2 people"<<endl;
        cout<<"Every round, each player rolls their dice and can do so up to 3x";
        cout<<"in a single turn."<<endl;
        cout<<"Then, the player will choose the category they want to use to";
        cout<<" accumulate points based on the combination of their dice."<<endl;
        cout<<"Ones: pts = sum of dice with 1 face."<<endl;
        cout<<"Twos: pts = sum of dice with 2 face."<<endl;
        cout<<"Threes: pts = sum of dice with 3 face."<<endl;
        cout<<"Fours: pts = sum of dice with 4 face."<<endl;
        cout<<"Fives: pts = sum of dice with 5 face."<<endl;
        cout<<"Sixes: pts = sum of dice with 6 face."<<endl;
        cout<<"Full House: a combination consisting of 3 dice of the same face and";
        cout<<" 2 of another face. (25 pts)."<<endl;
        cout<<"Four-of-a-Kind: at least 4 dice showing the same face. pts =";
        cout<<" sum of those 4 dice."<<endl;
        cout<<"Little Straight: dice showing 1-2-3-4-5 (30 pts)"<<endl;
        cout<<"Big Straight: dice showing 2-3-4-5-6 (30 pts)"<<endl;
        cout<<"Choice: pts = sum of the dice with any combination."<<endl;
        cout<<"Yacht: all 5 dice showing the same face. (50 pts)"<<endl;
        cout<<"Each category can only be used once in a single game."<<endl;
        cout<<"If a category is called and the combination isn't applicable,";
        cout<<" no points will be accumulated."<<endl;
        cout<<"Player with the most points will win prizes."<<endl;
    }
    cout<<endl;
    
//COUNTDOWN TO START THE GAME (USES A VECTOR)
    
    cntDown(begin);
    cout<<endl;
    
//PLAYERS START OUT WITH 0 POINTS
    
    points1 = 0;
    points2 = 0;
    
//GAME PLAY
    
    for (int i = 24; i >= 1; i--)   //each game is 12 turns for each player
    {
        if (i%2)    //Player 2's turn
        {
            
//DICE ROLL
            
            ag_pts = 0;         //The accumulator for the number of tries resets
                                //every time the player begins a new turn
            int array2[SIZE];   //initializing the array of dice every new turn
            cout<<endl;
            do
            {
                //Faces of the dice will be chosen at random
                array2[0] = dice21 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
                array2[1] = dice22 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
                array2[2] = dice23 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
                array2[3] = dice24 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
                array2[4] = dice25 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
            
                //Dice for the player - sorted and displayed
                cout<<name2<<" - your die are..."<<endl;
                bubSort(array2, SIZE);
                disAry(array2, SIZE);
                cout<<endl;
                
                //Players have the chance to roll their dice up to 3x in a single
                //turn
                cout<<"Would you like to roll your dice again? (y/n)"<<endl;
                cin>>again;
                if (again == 'y' || again == 'Y')
                {
                    ag_pts += 1;    //each time the player chooses to roll again,
                                    //it's added to this accumulator
                }
            } while ((again == 'Y' && ag_pts <= 2) || (again == 'y' && ag_pts <= 2));
            
            //A player cannot roll their dice more than 3x in a single turn
            if (again == 'y' && ag_pts > 2)
            {
                cout<<"Sorry - you cannot roll your dice more than 3 times in a ";
                cout<<"single turn"<<endl;
                cout<<"The game will continue now."<<endl<<endl;
            }
            
//SCORING CATEGORY TO USE
            
            //Which scoring category to use based on the dice combination
            //User can also view the categories they have left
            cout<<"Which scoring category would you like to use? ";
            cout<<"(no spaces or uppercase letters)";
            cout<<" (enter v to view your categories)."<<endl;
            cin>>scoCat;
            if (scoCat == "v")
            {
                cout<<endl;
                cout<<"CATEGORIES LEFT:"<<endl;
                prtAry(used2);
                cin>>scoCat;
            }
            
            //Making sure that user hasn't used the category previously
            while ((scoCat == "ones" && o2 != 0) || (scoCat == "twos" && t2 != 0) ||
                    (scoCat == "threes" && tr2 != 0) || (scoCat == "fours" && f2 != 0) ||
                    (scoCat == "fives" && fv2 != 0) || (scoCat == "sixes" && s2 != 0) ||
                    (scoCat == "fullhouse" && fh2 != 0) || (scoCat == "fourofakind" && k2 != 0) ||
                    (scoCat == "littlestraight" && ls2 != 0) || (scoCat == "bigstraight" && bs2 != 0) ||
                    (scoCat == "choice" && c2 != 0) || (scoCat == "yacht" && y2 != 0))
            {
                cout<<"You already used the category "<<scoCat<<"."<<endl;
                cout<<"Please choose a different category to continue."<<endl;
                cin>>scoCat;
                if (scoCat == "v")
                {
                    cout<<endl;
                    cout<<"CATEGORIES LEFT:"<<endl;
                    prtAry(used2);
                    cin>>scoCat;
                }
            }
            
//ONES
            
            if (scoCat == "ones")                   //pts = 1 * # of dice
            {
                int count;                          //How many times die with
                if (binSrch(array2, SIZE, 1))       //#1 face appeared
                {
                    count = val1(array2, SIZE, 1);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points2 += (1*count);
                
                o2 += 1;                            //indicates to the player
                used2[0][0] = "Used";               //that the category is used
                                                    //when displaying array
            }
            
//TWOS
            
            else if (scoCat == "twos")              //pts = 2 * # of dice
            {
                int count;
                if (binSrch(array2, SIZE, 2))
                {
                    count = val1(array2, SIZE, 2);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points2 += (2*count);
                
                t2 += 1;
                used2[0][1] = "Used";
            }
            
//THREES
            
            else if (scoCat == "threes")            //pts = 3 * # of dice
            {
                int count;
                if (binSrch(array2, SIZE, 3))
                {
                    count = val1(array2, SIZE, 3);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points2 += (3*count);
                
                tr2 += 1;
                used2[0][2] = "Used";
            }
            
//FOURS
            
            else if (scoCat == "fours")             //pts = 4 * # of dice
            {
                int count;
                if (binSrch(array2, SIZE, 4))
                {
                    count = val1(array2, SIZE, 4);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points2 += (4*count);
                
                f2 += 1;
                used2[0][3] = "Used";
            }
            
//FIVES
            
            else if (scoCat == "fives")             //pts = 5 * # of dice
            {
                int count;
                if (binSrch(array2, SIZE, 5))
                {
                    count = val1(array2, SIZE, 5);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points2 += (5*count);
                
                fv2 += 1;
                used2[1][0] = "Used";
            }
            
//SIXES
            
            else if (scoCat == "sixes")             //pts = 6 * # of dice
            {
                int count;
                if (binSrch(array2, SIZE, 6))
                {
                    count = val1(array2, SIZE, 6);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points2 += (6*count);
                
                s2 += 1;
                used2[1][1] = "Used";
            }
            
//FULL HOUSE
            
            else if (scoCat == "fullhouse")    
            {
                //there are only 10 combinations in which 3 out of the 5 dice
                //will be the same and the other 2 will also be the same
                if ((dice21 == dice22 && dice22 == dice23 && dice24 == dice25)
                || (dice21 == dice22 && dice22 == dice24 && dice23 == dice25)
                || (dice21 == dice22 && dice22 == dice25 && dice23 == dice24)
                || (dice21 == dice23 && dice23 == dice24 && dice22 == dice25)
                || (dice21 == dice23 && dice23 == dice25 && dice22 == dice24)
                || (dice21 == dice24 && dice24 == dice25 && dice22 == dice23)
                || (dice22 == dice23 && dice23 == dice24 && dice21 == dice25)
                || (dice22 == dice23 && dice23 == dice25 && dice21 == dice24)
                || (dice22 == dice24 && dice24 == dice25 && dice21 == dice23)
                || (dice25 == dice23 && dice23 == dice24 && dice21 == dice22))
                {
                    points2 += 25;
                }
                
                //no points will be accumulated if a player uses the category
                //but the dice combination doesn't actually match that category
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                fh2 += 1;
                used2[1][2] = "Used";
            }
            
//FOUR-OF-A-KIND
            
            else if (scoCat == "fourofakind")
            {
                //there are only 5 combinations where there can be 4 of dice
                //have the same face
                if ((dice21 == dice22 && dice22 == dice23 && dice23 == dice24)
                || (dice21 == dice22 && dice22 == dice23 && dice23 == dice25)
                || (dice24 == dice22 && dice22 == dice23 && dice23 == dice25)
                || (dice21 == dice23 && dice23 == dice24 && dice24 == dice25)
                || (dice21 == dice24 && dice24 == dice25 && dice25 == dice22))
                {
                    //finding the number that appeared at least 4x
                    //pts = that die * 4
                    int index = repeat(array2, SIZE);
                    (index == 1) ? points2 += (1*4) :
                    (index == 2) ? points2 += (2*4) :
                    (index == 3) ? points2 += (3*4) :
                    (index == 4) ? points2 += (4*4) :
                    (index == 5) ? points2 += (5*4) : points2 += (6*4);
                }
                
                //no points will be accumulated if a player uses the category
                //but the dice combination doesn't actually match that category
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                k2 += 1;
                used2[1][3] = "Used";
            }
            
//LITTLE STRAIGHT
            
            else if (scoCat == "littlestraight")
            {
                //Making sure that the dice do indeed match the required
                //combination
                if (dice21 == 1 && dice22 == 2 && dice23 == 3 && dice24 == 4
                && dice25 == 5)
                {
                    points2 += 30;
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                ls2 += 1;
                used2[2][0] = "Used";
            }
            
//BIG STRAIGHT
            
            else if (scoCat == "bigstraight")
            {
                //Making sure that the dice do indeed match the required
                //combination
                if ((dice21 == 2) && (dice22 == 3) && (dice23 == 4) && (dice24 == 5)
                && (dice25 == 6))
                {
                    points2 += 30;
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                bs2 += 1;
                used2[2][1] = "Used";
            }
            
//CHOICE
            
            else if (scoCat == "choice")    //pts = the sum of all the dice faces
            {
                points2 += (dice21+dice22+dice23+dice24+dice25);
                
                c2 += 1;
                used2[2][2] = "Used";
            }
            
//YACHT
            
            else if (scoCat == "yacht")     //all faces must be the same
            {
                if (dice21 == dice22 && dice22 == dice23 && dice23 == dice24
                && dice24 == dice25)
                {
                    points2 += 50;
                }
                
                //no points will be accumulated if a player uses the category
                //but the dice combination doesn't actually match that category
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                y2 += 1;
                used2[2][3] = "Used";
            }      
        }
        
//COMMENTS FOR PLAYER 1 ARE THE SAME FOR PLAYER 2
        
        else    //Player 1's turn
        {
//DICE ROLL
            
            ag_pts = 0;         //The accumulator for the number of tries resets
                                //every time the player begins a new turn
            int array1[SIZE];   //initializing the array of dice every new turn
            cout<<endl;
            do
            {
                //Faces of the dice will be chosen at random
                array1[0] = dice11 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
                array1[1] = dice12 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
                array1[2] = dice13 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
                array1[3] = dice14 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
                array1[4] = dice15 = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
            
                //Dice for the player - sorted and displayed
                cout<<name1<<" - your die are..."<<endl;
                selSort(array1, SIZE);
                disAry(array1, SIZE);
                cout<<endl;
                
                //Players have the chance to roll their dice up to 3x in a single
                //turn
                cout<<"Would you like to roll your dice again? (y/n)"<<endl;
                cin>>again;
                if (again == 'y' || again == 'Y')
                {
                    ag_pts += 1;    //each time the player chooses to roll again,
                                    //it's added to this accumulator
                }
            } while ((again == 'Y' && ag_pts <= 2) || (again == 'y' && ag_pts <= 2));
            
            //A player cannot roll their dice more than 3x in a single turn
            if (again == 'y' && ag_pts > 2)
            {
                cout<<"Sorry - you cannot roll your dice more than 3 times in a ";
                cout<<"single turn"<<endl;
                cout<<"The game will continue now."<<endl<<endl;
            }
            
//SCORING CATEGORY TO USE
            
            //Which scoring category to use based on the dice combination
            //User can also view the categories they have left
            cout<<"Which scoring category would you like to use? ";
            cout<<"(no spaces or uppercase letters)";
            cout<<" (enter v to view your categories)."<<endl;
            cin>>scoCat;
            if (scoCat == "v")
            {
                cout<<"CATEGORIES LEFT:"<<endl;
                prtAry(used1);
                cin>>scoCat;
            }
            
            //Making sure that user hasn't used the category previously
            while ((scoCat == "ones" && o1 != 0) || (scoCat == "twos" && t1 != 0) ||
                    (scoCat == "threes" && tr1 != 0) || (scoCat == "fours" && f1 != 0) ||
                    (scoCat == "fives" && fv1 != 0) || (scoCat == "sixes" && s1 != 0) ||
                    (scoCat == "fullhouse" && fh1 != 0) || (scoCat == "fourofakind" && k1 != 0) ||
                    (scoCat == "littlestraight" && ls1 != 0) || (scoCat == "bigstraight" && bs1 != 0) ||
                    (scoCat == "choice" && c1 != 0) || (scoCat == "yacht" && y1 != 0))
            {
                cout<<"You already used the category "<<scoCat<<"."<<endl;
                cout<<"Please choose a different category to continue."<<endl;
                cin>>scoCat;
                if (scoCat == "v")
                {
                    cout<<endl;
                    cout<<"CATEGORIES LEFT:"<<endl;
                    prtAry(used1);
                    cin>>scoCat;
                }
            }
            
//ONES
            
            if (scoCat == "ones")                   //pts = 1 * # of dice
            {
                int count;                          //How many times die with
                if (binSrch(array1, SIZE, 1))       //#1 face appeared
                {
                    count = val1(array1, SIZE, 1);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points1 += (1*count);
                
                o1 += 1;                            //indicates to the player
                used1[0][0] = "Used";               //that the category is used
                                                    //when displaying array
            }
            
//TWOS
            
            else if (scoCat == "twos")              //pts = 2 * # of dice
            {
                int count;
                if (binSrch(array1, SIZE, 2))
                {
                    count = val1(array1, SIZE, 2);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points1 += (2*count);
                
                t1 += 1;
                used1[0][1] = "Used";
            }
            
//THREES
            
            else if (scoCat == "threes")            //pts = 3 * # of dice
            {
                int count;
                if (binSrch(array1, SIZE, 3))
                {
                    count = val1(array1, SIZE, 3);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points1 += (3*count);
                
                tr1 += 1;
                used1[0][2] = "Used";
            }
            
//FOURS
            
            else if (scoCat == "fours")             //pts = 4 * # of dice
            {
                int count;
                if (binSrch(array1, SIZE, 4))
                {
                    count = val1(array1, SIZE, 4);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points1 += (4*count);
                
                f1 += 1;
                used1[0][3] = "Used";
            }
            
//FIVES
            
            else if (scoCat == "fives")             //pts = 5 * # of dice
            {
                int count;
                if (binSrch(array1, SIZE, 5))
                {
                    count = val1(array1, SIZE, 5);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points1 += (5*count);
                
                fv1 += 1;
                used1[1][0] = "Used";
            }
            
//SIXES
            
            else if (scoCat == "sixes")             //pts = 6 * # of dice
            {
                int count;
                if (binSrch(array1, SIZE, 6))
                {
                    count = val1(array1, SIZE, 6);
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                points1 += (6*count);
                
                s1 += 1;
                used1[1][1] = "Used";
            }
            
//FULL HOUSE
            
            else if (scoCat == "fullhouse")    
            {
                //there are only 10 combinations in which 3 out of the 5 dice
                //will be the same and the other 2 will also be the same
                if ((dice11 == dice12 && dice12 == dice13 && dice14 == dice15)
                || (dice11 == dice12 && dice12 == dice14 && dice13 == dice15)
                || (dice11 == dice12 && dice12 == dice15 && dice13 == dice14)
                || (dice11 == dice13 && dice13 == dice14 && dice12 == dice15)
                || (dice11 == dice13 && dice13 == dice15 && dice12 == dice14)
                || (dice11 == dice14 && dice14 == dice15 && dice12 == dice13)
                || (dice12 == dice13 && dice13 == dice14 && dice11 == dice15)
                || (dice12 == dice13 && dice13 == dice15 && dice11 == dice14)
                || (dice12 == dice14 && dice14 == dice15 && dice11 == dice13)
                || (dice15 == dice13 && dice13 == dice14 && dice11 == dice12))
                {
                    points1 += 25;
                }
                
                //no points will be accumulated if a player uses the category
                //but the dice combination doesn't actually match that category
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                fh1 += 1;
                used1[1][2] = "Used";
            }
            
//FOUR-OF-A-KIND
            
            else if (scoCat == "fourofakind")
            {
                //there are only 5 combinations where there can be 4 of dice
                //have the same face
                if ((dice11 == dice12 && dice12 == dice13 && dice13 == dice14)
                || (dice11 == dice12 && dice12 == dice13 && dice13 == dice15)
                || (dice14 == dice12 && dice12 == dice13 && dice13 == dice15)
                || (dice11 == dice13 && dice13 == dice14 && dice14 == dice15)
                || (dice11 == dice14 && dice14 == dice15 && dice15 == dice12))
                {
                    //finding the number that appeared at least 4x
                    //pts = that die * 4
                    int index = repeat(array1, SIZE);
                    (index == 1) ? points1 += (1*4) :
                    (index == 2) ? points1 += (2*4) :
                    (index == 3) ? points1 += (3*4) :
                    (index == 4) ? points1 += (4*4) :
                    (index == 5) ? points1 += (5*4) : points1 += (6*4);
                }
                
                //no points will be accumulated if a player uses the category
                //but the dice combination doesn't actually match that category
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                k1 += 1;
                used1[1][3] = "Used";
            }
            
//LITTLE STRAIGHT
            
            else if (scoCat == "littlestraight")
            {
                //Making sure that the dice do indeed match the required
                //combination
                if (dice11 == 1 && dice12 == 2 && dice13 == 3 && dice14 == 4
                && dice15 == 5)
                {
                    points1 += 30;
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                ls1 += 1;
                used1[2][0] = "Used";
            }
            
//BIG STRAIGHT
            
            else if (scoCat == "bigstraight")
            {
                //Making sure that the dice do indeed match the required
                //combination
                if ((dice11 == 2) && (dice12 == 3) && (dice13 == 4) && (dice14 == 5)
                && (dice15 == 6))
                {
                    points1 += 30;
                }
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                bs1 += 1;
                used1[2][1] = "Used";
            }
            
//CHOICE
            
            else if (scoCat == "choice")    //pts = the sum of all the dice faces
            {
                points1 += (dice11+dice12+dice13+dice14+dice15);
                
                c1 += 1;
                used1[2][2] = "Used";
            }
            
//YACHT
            
            else if (scoCat == "yacht")     //all faces must be the same
            {
                if (dice11 == dice12 && dice12 == dice13 && dice13 == dice14
                && dice14 == dice15)
                {
                    points1 += 50;
                }
                
                //no points will be accumulated if a player uses the category
                //but the dice combination doesn't actually match that category
                else
                {
                    cout<<"Oops - looks like your combination doesn't match the category!"<<endl;
                    cout<<"No points will be accumulated."<<endl;
                }
                
                y1 += 1;
                used1[2][3] = "Used";
            }      
        }
        cout<<endl;
        
//ROUND RESULTS
        
        sep1(name1, name2);
        cout<<endl;
        cout<<"TOTAL POINTS SO FAR: ";
        cout<<points(points1)<<" for "<<name1<<" and ";
        cout<<points(points2)<<" for "<<name2<<"."<<endl;
        sep1(name1, name2);
        cout<<endl;
        
        //Outputting the same data to the file
        game<<"TOTAL POINTS FROM TURN "<<i<<": ";
        game<<static_cast<int>(pow(points1, 1))<<" for "<<name1<<" and ";
        game<<static_cast<int>(pow(points2, 1))<<" for "<<name2<<"."<<endl;
        game<<endl;
    }
    
//WINNER OF THE GAME
    
    cout<<endl;
    sep2(name1, name2);
    cout<<endl;
    cout<<"TOTAL POINTS:"<<endl;
    cout<<name1<<": "<<setprecision(2)<<fixed<<showpoint<<points1<<endl;
    cout<<name2<<": "<<setprecision(2)<<fixed<<showpoint<<points2<<endl;
    if (win(points1, points2))
    {
        cout<<name1<<" is the WINNER!"<<endl; 
    }
    else
    {
        cout<<name2<<" is the WINNER!"<<endl;
    }
    sep2(name1, name2);
    cout<<endl;
    
    //Outputting the same data to a file
    game<<endl;
    game<<"TOTAL POINTS:"<<endl<<endl;
    game<<name1<<": "<<setprecision(2)<<fixed<<showpoint<<points1<<endl;
    game<<name2<<": "<<setprecision(2)<<fixed<<showpoint<<points2<<endl;
    
    if (win(points1, points2))     //if the bool statement is true, then player 1 is the winner
    {
        game<<name1<<" is the WINNER!"<<endl; 
    }
    else            //if bool statement is false, then player 2 is the winner
    {
        game<<name2<<" is the WINNER!"<<endl;
    }
    cout<<endl;
    
//WINNER'S PRIZE
    
    cout<<"Pick a prize from the mystery box. (pick a # from 1-5)"<<endl;
    cin>>myst;
    if (myst < 1 || myst > 5)   //User-validation for mystery box
    {
        cout<<"Oops - the mystery box only has five prizes at the moment."<<endl;
        cout<<"Please enter a valid number (1-5) to get a prize."<<endl;
        cin>>myst;
    }
    else
    {
        prize(myst);
    }
    
//CLOSING THE FILE AND EXITING MAIN
    
    //Watch Your Step...
    game.close();
    return 0;
}

int points(float pts)
{
    pts = pow(pts, 1);
    return pts;         //returns points for the player
}

bool win(float pts1, float pts2)
{
    static bool winner;
    
    if (pts1 > pts2)    //if Player 1's points is more, then Player 1 is the winner
    {
        winner = true;
    }
    else                //if Player 2's points is more, then Player 2 is the winner
    {
        winner = false;
    }
    
    return winner;      //returns if (player 1 > player 2) is true or false
}

void sep1(string &name1, string &name2, int length)
{
    int size1 = name1.size();   //name size of Player 1
    int size2 = name2.size();   //name size of Player 2
    int totlSep;                //total '*' to include
    
    if (size1 > size2)          //total '*' to include must be as long as the
                                //player with the name of higher size
    {
        totlSep = size1 + length;
    }
    else
    {
        totlSep = size2 + length;
    }
    
    for (int i = 0; i <= totlSep; i++)
    {
        cout<<"*";
    }
}

void sep2(string &name1, string &name2, float length)
{
    int size1 = name1.size();
    int size2 = name2.size();
    int totlSep;
    
    if (size1 > size2)
    {
        totlSep = size1 + length;
    }
    else
    {
        totlSep = size2 + length;
    }
    
    for (int i = 0; i <= totlSep; i++)
    {
        cout<<"*";
    }
}

void sep(int length)
{
    for (int i = 0; i <= length; i++)
    {
        cout<<"*";
    }
    cout<<endl;
}
void sep(int length1, int length2)
{
    int totl = length1 * length2;
    for (int i = 0; i <= totl; i++)
    {
        cout<<"*";
    }
    cout<<endl;
}

int val1(int array[], int SIZE, int num)
{
    int repeat = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (array[i] == num)    //if integer in array = the num to look for, then
                                //it's added to the 'repeat' accumulator
        {
            repeat += 1;
        }
    }
    return repeat;              //returns the amount of times the number was
                                //repeated
                                //if repeat = 0, it means that the number we're
                                //trying to find wasn't in the array
}

void bubSort(int array[], int SIZE) //Bubble Sort
{
    int maxNum;
    int index;
    for (maxNum = SIZE-1; maxNum > 0; maxNum--)
    {
        for (index = 0; index < maxNum; index++)
        {
            if (array[index] > array[index+1])
            {
                swap(array[index], array[index+1]);
            }
        }
    }
}

void disAry(int array[], int SIZE)  //displays every integer in the dice
                                    //combination array
{
    for (int i = 0; i < SIZE; i++)
    {
        cout<<array[i]<<" ";
    }
}

void selSort(int array[], int SIZE) //Selection Sort
{
    int minInd, minVal;
    
    for (int i = 0; i < (SIZE-1); i++)
    {
        minInd = i;
        minVal = array[i];
        for (int j = i+1; j < SIZE; j++)
        {
            if (array[j] < minVal)
            {
                minVal = array[j];
                minInd = j;
            }
        }
        swap(array[minInd], array[i]);
    }
}

bool binSrch(int array[], int SIZE, int num)    //Binary Search
{
    int first = 0;
    int last = SIZE - 1;
    int middle;
    bool found = false;
    
    while (!found && first <= last)
    {
        middle = (first + last)/2;
        if (array[middle] == num)
        {
            found = true;
        }
        else if (array[middle] > num)
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1;
        }
    }
    return found;         //returns if the number we were looking for is
                          //actually there or not
}

void prtAry(string array[3][4])     //prints an array for every category in the
                                    //array, used or not
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout<<setw(17)<<array[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}

void cntDown(vector<int> vect)          //countdown to the beginning of the game
{
    for (int i = 0; i < 3; i++)
    {
        cout<<vect[i]<<" . . . ";
    }
    cout<<"LET'S BEGIN!";
}

void prize(int num) //allows the player to pick their prize
{
    switch (num)   //Different prizes that are inside the mystery box
    {
        case 1 : 
            cout<<"Your prize is an imaginary private island!"<<endl;
            exit(0);
        case 2 : 
            cout<<"Your prize is a piece of advice from Dr. Lehr!"<<endl;
            exit(0);
        case 3 : 
            cout<<"Your prize is the antidote for old-fart programming!"<<endl;
            exit(0);
        case 4 : 
            cout<<"Your prize is a life-time supply of diet coke!"<<endl;
            exit(0);
        case 5 : 
            cout<<"Your prize is an imaginary dollar!"<<endl;
            exit(0);
    }
}

int repeat(int array[], int SIZE)
{
    int num;
    for (int i = 0; i < SIZE - 1; i++)
    {
        for (int j = i+1; j < SIZE; j++)
        {
            if (array[i] == array[j])   //if both numbers are the same, then that
                                        //number was repeated
            {
                num = array[i];         //num = the repeated number
            }
        }
    }
    return num;     //returns the number of times the integer was repeated
}

/* * * * * * * * * * * * * * *
 * Yours Truly,              *
 * Sara Hussin               *
 * on 06/03/2022 @ 9:42 PM   *
 * * * * * * * * * * * * * * */
