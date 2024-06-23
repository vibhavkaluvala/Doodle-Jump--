//Imports
#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include "../simulator_libraries/FEHImages.h"
//Screen width and height
#define WIDTH 320
#define HEIGHT 240
//Max value returned by random function
#define RANDMAX 32767.0
//Width and height of character model
#define FILLWIDTH 25
#define FILLHEIGHT 25
//How much score increases
#define SCORE 50
//Global variables for scores and time
int maxScore = 0;
int lastScore = 0;
float longestTime = 0;
//Stats class and Play class prototype
class Stats;
class Play;
//Status struct prototype
struct status;
//Function Prototypes
bool checkCollision(int, int, status);
void createPlatform(int, int);
void drawAllPlatforms(status);
void clearAllPlatforms(status);
void generateFirstPlatform(int[]);
void generateSecondPlatform(int[]);
void generateThirdPlatform(int[]);
void generateNewRow(status);
void generateInitialPlatforms(status);
void movePlatformsIncrement(status, int);
void player_sprite(int, int, bool);
void scrollDown(status);
void backButton();
bool VerticalMovement(status, bool, Stats);
void Credits();
void Instructions();
void DrawMenu(Stats, Play);
/*
--status Struct--
Struct contains information for character and platforms
Contains:
 array for characters base coordinates
 character previous x position
 if character is facing left
 if character was facing left before
 arrays of platform x positions for all 6 rows of platforms
 platform y positions for all 6 rows of platforms
~Surya Suresh
*/
struct status{
 //Character coordinates
 int coordinates[2] = {140, 195};
 //Previous x position
 int prevX = 140;
 //If character is facing left
 bool left = true;
 //If character was previously facing left
 bool prevLeft = true;
 //Platform x coordinates for all 6 rows
 int platformX0[3] = {1000, 1000, 1000};
 int platformX1[3] = {1000, 1000, 1000};
 int platformX2[3] = {1000, 1000, 1000};
 int platformX3[3] = {1000, 1000, 1000};
 int platformX4[3] = {1000, 1000, 1000};
 int platformX5[3] = {1000, 1000, 1000};
 int platformX6[3] = {1000, 1000, 1000};
 //Platform y coordinates for all 6 rows
 int platformY0 = 200;
 int platformY1 = 150;
 int platformY2 = 100;
 int platformY3 = 50;
 int platformY4 = 0;
 int platformY5 = -50;
 int platformY6 = -100;
};
/*
--player_sprite Function--
The function draws the character at the coordinates.
Draws the character facing left or right depending on
the value of the boolean left.
Parameters:
 x - x coordinate of player
 y - y coordinate of player
 left - whether or not the player is facing left
Draws:
 draws the character model at the coordinates
~Luke Westerkamp
*/
void player_sprite(int x, int y, bool left){
 FEHImage player;
 if(left){
 player.Open("./lib/spriteLeft.pic");
 }else{
 player.Open("./lib/spriteRight.pic");
 }
 player.Draw(x,y);
 player.Close();
}
/*
--checkCollision Function--
The function checks if the character is colliding with any platform
and returns true if so or false if not.
Parameters:
 x - x position of character
 y - y position of character
 *Game - pointer to status struct
Returns:
 whether or not the character is colliding with a platform
~Surya Suresh
*/
bool checkCollision(int x, int y, status *Game){
 //Checks if character y position is within bounds of first platform row
 if(y >= (*Game).platformY0 - 25 && y <= (*Game).platformY0 - 15){
 //Iterate through all 3 platforms
 for(int i = 0; i < 3; i++){
 //Checks if character x position is within bounds of current index platform
 if(x + 12.5 >= (*Game).platformX0[i] && x + 12.5 <=
(*Game).platformX0[i] + 30){
 return true;
 }
 }
 }

 //Checks if character y position is within bounds of second platform row
 if(y >= (*Game).platformY1 - 25 && y <= (*Game).platformY1 - 15){
 for(int i = 0; i < 3; i++){
 //Checks if character x position is within bounds of current index
platform
 if(x + 12.5 >= (*Game).platformX1[i] && x + 12.5 <=
(*Game).platformX1[i] + 30){
 return true;
 }
 }
 }
 //Checks if character y position is within bounds of third platform row
 if(y >= (*Game).platformY2 - 25 && y <= (*Game).platformY2 - 15){
 for(int i = 0; i < 3; i++){
 //Checks if character x position is within bounds of current index
platform
 if(x + 12.5 >= (*Game).platformX2[i] && x + 12.5 <=
(*Game).platformX2[i] + 30){
 return true;
 }
 }
 }
 //Checks if character y position is within bounds of fourth platform row
 if(y >= (*Game).platformY3 - 25 && y <= (*Game).platformY3 - 15){
 for(int i = 0; i < 3; i++){
 //Checks if character x position is within bounds of current index
platform
 if(x + 12.5 >= (*Game).platformX3[i] && x + 12.5 <=
(*Game).platformX3[i] + 30){
 return true;
 }
 }
 }
 //Checks if character y position is within bounds of fifth platform row
 if(y >= (*Game).platformY4 - 25 && y <= (*Game).platformY4 - 15){
 for(int i = 0; i < 3; i++){
 //Checks if character x position is within bounds of current index
platform
 if(x + 12.5 >= (*Game).platformX4[i] && x + 12.5 <=
(*Game).platformX4[i] + 30){
 return true;
 }
 }
 }
 //Checks if character y position is within bounds of sixth platform row
 if(y >= (*Game).platformY5 - 25 && y <= (*Game).platformY5 - 15){
 for(int i = 0; i < 3; i++){
 //Checks if character x position is within bounds of current index
platform
 if(x + 12.5 >= (*Game).platformX5[i] && x + 12.5 <=
(*Game).platformX5[i] + 30){
 return true;
 }
 }
 }
 //Checks if character y position is within bounds of seventh platform row
 if(y >= (*Game).platformY6 - 25 && y <= (*Game).platformY6 - 15){
 for(int i = 0; i < 3; i++){
 //Checks if character x position is within bounds of current index
platform
 if(x + 12.5 >= (*Game).platformX6[i] && x + 12.5 <=
(*Game).platformX6[i] + 30){
 return true;
 }
 }
 }
 //If function has not found a collision, returns false
 return false;
}
/*
--createPlatform Function--
The function draws a platform at the coordinates provided.
Parameters:
 x - x position of platform
 y - y position of platform
Draws:
 draws a platform at the coordinates inputted
~Vibhav Kaluvala
*/
void createPlatform(int x, int y){
 //Created new FEHImage for platform
 FEHImage platform;
 //Opens platform pic file
 platform.Open("./lib/platform.pic");
 //Draws platform at coordinates
 platform.Draw(x, y);
 //Closes platform object
 platform.Close();
}
/*
--drawAllPlatforms Function--
The function draws all platforms in range onto the screen.
Function iterates through each x position array and calls
createPlatform function for each one.
Parameters:
 *Game - pointer to status struct
Draws:
 draws all platforms onto the screen
~Vibhav Kaluvala
*/
void drawAllPlatforms(status *Game){
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX0[i] != 1000 && (*Game).platformY0 > 0){
 //Calls createPlatform to draw platform at coordinates
 createPlatform((*Game).platformX0[i], (*Game).platformY0);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX1[i] != 1000 && (*Game).platformY1 > 0){
 //Calls createPlatform to draw platform at coordinates
 createPlatform((*Game).platformX1[i], (*Game).platformY1);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX2[i] != 1000 && (*Game).platformY2 > 0){
 //Calls createPlatform to draw platform at coordinates
 createPlatform((*Game).platformX2[i], (*Game).platformY2);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX3[i] != 1000 && (*Game).platformY3 > 0){
 //Calls createPlatform to draw platform at coordinates
 createPlatform((*Game).platformX3[i], (*Game).platformY3);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX4[i] != 1000 && (*Game).platformY4 > 0){
 //Calls createPlatform to draw platform at coordinates
 createPlatform((*Game).platformX4[i], (*Game).platformY4);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX5[i] != 1000 && (*Game).platformY5 > 0){
 //Calls createPlatform to draw platform at coordinates
 createPlatform((*Game).platformX5[i], (*Game).platformY5);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX6[i] != 1000 && (*Game).platformY6 > 0){
 //Calls createPlatform to draw platform at coordinates
 createPlatform((*Game).platformX6[i], (*Game).platformY6);
 }
 }
}
/*
--clearAllPlatforms Function--
The function draws rectangles over platforms in range onto the screen.
Function iterates through each x position array and draws
a rectangle at all of them.
Parameters:
 *Game - pointer to status struct
Draws:
 covers all platforms on the screen
~Vibhav Kaluvala
*/
void clearAllPlatforms(status *Game){
 //Sets font color to background color
 LCD.SetFontColor(ANTIQUEWHITE);
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX0[i] != 1000 && (*Game).platformY0 > 0){
 //Draws filled rectangle at coordinates
 LCD.FillRectangle((*Game).platformX0[i], (*Game).platformY0, 30, 10);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX1[i] != 1000 && (*Game).platformY1 > 0){
 //Draws filled rectangle at coordinates
 LCD.FillRectangle((*Game).platformX1[i], (*Game).platformY1, 30, 10);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX2[i] != 1000 && (*Game).platformY2 > 0){
 //Draws filled rectangle at coordinates
 LCD.FillRectangle((*Game).platformX2[i], (*Game).platformY2, 30, 10);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX3[i] != 1000 && (*Game).platformY3 > 0){
 //Draws filled rectangle at coordinates
 LCD.FillRectangle((*Game).platformX3[i], (*Game).platformY3, 30, 10);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX4[i] != 1000 && (*Game).platformY4 > 0){
 //Draws filled rectangle at coordinates
 LCD.FillRectangle((*Game).platformX4[i], (*Game).platformY4, 30, 10);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX5[i] != 1000 && (*Game).platformY5 > 0){
 //Draws filled rectangle at coordinates
 LCD.FillRectangle((*Game).platformX5[i], (*Game).platformY5, 30, 10);
 }
 }
 //Increments through all three possible platforms
 for(int i = 0; i < 3; i++){
 //Checks if platform X is not placeholder 1000 and if its visible on screen
 if((*Game).platformX6[i] != 1000 && (*Game).platformY6 > 0){
 //Draws filled rectangle at coordinates
 LCD.FillRectangle((*Game).platformX6[i], (*Game).platformY6, 30, 10);
 }
 }
}
/*
--generateFirstPlatform Function--
The function generates a random number in the bounds of the screen
and sets the x position of the first element of the x position array
to the random number. Ensures that the enture platform is on screen
by setting right side bound.
Parameters:
 platform[] - pointer to array of x positions
Sets:
 sets position of first element of array to random number
~Surya Suresh
*/
void generateFirstPlatform(int platform[]){
 //Calls RandInt and divides by randmax to get a random number between 0 and 1
 float randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 //Multiplies random number between 0 and 1 by width of screen to get a random x
coordinate
 int randX = randomNormal * WIDTH;
 //If x position is greater than width of screen minutes width of platform
 //then sets x coordinate to 290
 if(randX > 290){
 platform[0] = 290;
 }else{
 platform[0] = randX;
 }
}
/*
--generateSecondPlatform Function--
The function generates a random number in the bounds of the screen
and sets the x position of the first element of the x position array
to the random number. Ensures that the enture platform is on screen
by setting right side bound. Ensures that the platform does not overlap
with the first plaform generated.
Parameters:
 platform[] - pointer to array of x positions
Sets:
 sets position of second element of array to random number
~Surya Suresh
*/
void generateSecondPlatform(int platform[]){
 //Sets overlap boolean to false
 bool overlap = false;
 //While there is no overlap
 while(!overlap){
 //Calls RandInt and divides by randmax to get a random number between 0 and
1
 float randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 //Multiplies random number between 0 and 1 by width of screen to get a
random x coordinate
 int randX = randomNormal * WIDTH;

 //Checks if there is overlap between the new x coordinate and the first
platform
 if(randX < platform[0] - 30 || randX > platform[0] + 30){
 if(randX < 290){
 platform[1] = randX;
 overlap = true;
 }
 }
 }
}
/*
--generateThirdPlatform Function--
The function generates a random number in the bounds of the screen
and sets the x position of the first element of the x position array
to the random number. Ensures that the enture platform is on screen
by setting right side bound. Ensures that the platform does not overlap
with the first or second plaform generated.
Parameters:
 platform[] - pointer to array of x positions
Sets:
 sets position of third element of array to random number
~Surya Suresh
*/
void generateThirdPlatform(int platform[]){

 //Sets overlap boolean to false
 bool overlap = false;
 while(!overlap){
 //Calls RandInt and divides by randmax to get a random number between 0 and
1
 float randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 //Multiplies random number between 0 and 1 by width of screen to get a
random x coordinate
 int randX = randomNormal * WIDTH;

 //Checks if there is overlap between the new x coordinate and the first and
second platform
 if((randX < platform[0] - 30 || randX > platform[0] + 30) && (randX <
platform[1] - 30 || randX > platform[1] + 30)){
 if(randX < 290){
 platform[1] = randX;
 overlap = true;
 }
 }
 }
}
/*
--generateNewRow Function--
The function generates new values for row 7, the top row.
Calls generateFirstPlatform, and if applicable, generateSecondPlatform
and generateThirdPlatform.
Parameters:
 *Game - pointer to status struct
Sets:
 sets the values of the row 6 array to new randomly generated x coordinates
~Surya Suresh
*/
void generateNewRow(status *Game){

 //Generates a random number of platforms from 1 to 3
 float randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 int numPlatforms = 1 + randomNormal * 3;

 //Generates the first platform
 generateFirstPlatform((*Game).platformX6);
 //Checks if theres more than 1 platform
 if(numPlatforms > 1){
 //Generates the second platform
 generateSecondPlatform((*Game).platformX6);
 //Checks if theres more than 2 platforms
 if(numPlatforms > 2){
 //Generates the third platform
 generateThirdPlatform((*Game).platformX6);
 }else{
 //Otherwise sets the third platform coordinate to 1000
 (*Game).platformX6[2] = 1000;
 }
 }else{
 //Otherwise sets the first and second platform coordinates to 1000
 (*Game).platformX6[1] = 1000;
 (*Game).platformX6[2] = 1000;
 }
}
/*
--generateNewRow Function--
The function generates platform coordinates for all 7 rows.
Calls generateFirstPlatform, and if applicable, generateSecondPlatform
and generateThirdPlatform.
Parameters:
 *Game - pointer to status struct
Sets:
 sets the coordinate values of all row arrays to new randomly generated values
~Surya Suresh
*/
void generateInitialPlatforms(status *Game){
 //Generates a random number of platforms from 1 to 3
 float randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 int numPlatforms = 1 + randomNormal * 3;

 //Generates the first platform
 generateFirstPlatform((*Game).platformX0);
 //Checks if there is more than 1 platform
 if(numPlatforms > 1){
 //Generates the second platform
 generateSecondPlatform((*Game).platformX0);
 //Checks if there is more than 2 platforms
 if(numPlatforms > 2){
 //Generates the third platform
 generateThirdPlatform((*Game).platformX0);
 }else{
 //Otherwise sets the third platform coordinate to 1000
 (*Game).platformX0[2] = 1000;
 }
 }else{
 //Otherwise sets the first and second platform coordinates to 1000
 (*Game).platformX0[1] = 1000;
 (*Game).platformX0[2] = 1000;
 }
 //Generates a random number of platforms from 1 to 3
 randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 numPlatforms = 1 + randomNormal * 3;

 //Generates the first platform
 generateFirstPlatform((*Game).platformX1);
 //Checks if there is more than 1 platform
 if(numPlatforms > 1){
 //Generates the second platform
 generateSecondPlatform((*Game).platformX1);
 //Checks if there is more than 2 platforms
 if(numPlatforms > 2){
 //Generates the third platform
 generateThirdPlatform((*Game).platformX1);
 }else{
 //Otherwise sets the third platform coordinate to 1000
 (*Game).platformX1[2] = 1000;
 }
 }else{
 //Otherwise sets the first and second platform coordinates to 1000
 (*Game).platformX1[1] = 1000;
 (*Game).platformX1[2] = 1000;
 }

 //Generates a random number of platforms from 1 to 3
 randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 numPlatforms = 1 + randomNormal * 3;
 //Generates the first platform
 generateFirstPlatform((*Game).platformX2);
 //Checks if there is more than 1 platform
 if(numPlatforms > 1){
 //Generates the second platform
 generateSecondPlatform((*Game).platformX2);
 //Checks if there is more than 2 platforms
 if(numPlatforms > 2){
 //Generates the third platform
 generateThirdPlatform((*Game).platformX2);
 }else{
 //Otherwise sets the third platform coordinate to 1000
 (*Game).platformX2[2] = 1000;
 }
 }else{
 //Otherwise sets the first and second platform coordinates to 1000
 (*Game).platformX2[1] = 1000;
 (*Game).platformX2[2] = 1000;
 }
 //Generates a random number of platforms from 1 to 3
 randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 numPlatforms = 1 + randomNormal * 3;

 //Generates the first platform
 generateFirstPlatform((*Game).platformX3);
 //Checks if there is more than 1 platform
 if(numPlatforms > 1){
 //Generates the second platform
 generateSecondPlatform((*Game).platformX3);
 //Checks if there is more than 2 platforms
 if(numPlatforms > 2){
 //Generates the third platform
 generateThirdPlatform((*Game).platformX3);
 }else{
 //Otherwise sets the third platform coordinate to 1000
 (*Game).platformX3[2] = 1000;
 }
 }else{
 //Otherwise sets the first and second platform coordinates to 1000
 (*Game).platformX3[1] = 1000;
 (*Game).platformX3[2] = 1000;
 }
 //Generates a random number of platforms from 1 to 3
 randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 numPlatforms = 1 + randomNormal * 3;

 //Generates the first platform
 generateFirstPlatform((*Game).platformX4);
 //Checks if there is more than 1 platform
 if(numPlatforms > 1){
 //Generates the second platform
 generateSecondPlatform((*Game).platformX4);
 //Checks if there is more than 2 platforms
 if(numPlatforms > 2){
 //Generates the third platform
 generateThirdPlatform((*Game).platformX4);
 }else{
 //Otherwise sets the third platform coordinate to 1000
 (*Game).platformX4[2] = 1000;
 }
 }else{
 //Otherwise sets the first and second platform coordinates to 1000
 (*Game).platformX4[1] = 1000;
 (*Game).platformX4[2] = 1000;
 }
 //Generates a random number of platforms from 1 to 3
 randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 numPlatforms = 1 + randomNormal * 3;

 //Generates the first platform
 generateFirstPlatform((*Game).platformX5);
 //Checks if there is more than 1 platform
 if(numPlatforms > 1){
 //Generates the second platform
 generateSecondPlatform((*Game).platformX5);
 //Checks if there is more than 2 platforms
 if(numPlatforms > 2){
 //Generates the third platform
 generateThirdPlatform((*Game).platformX5);
 }else{
 //Otherwise sets the third platform coordinate to 1000
 (*Game).platformX5[2] = 1000;
 }
 }else{
 //Otherwise sets the first and second platform coordinates to 1000
 (*Game).platformX5[1] = 1000;
 (*Game).platformX5[2] = 1000;
 }
 //Generates a random number of platforms from 1 to 3
 randomNormal = ((1.0) * Random.RandInt()) / RANDMAX;
 numPlatforms = 1 + randomNormal * 3;

 //Generates the first platform
 generateFirstPlatform((*Game).platformX6);
 //Checks if there is more than 1 platform
 if(numPlatforms > 1){
 //Generates the second platform
 generateSecondPlatform((*Game).platformX6);
 //Checks if there is more than 2 platforms
 if(numPlatforms > 2){
 //Generates the third platform
 generateThirdPlatform((*Game).platformX6);
 }else{
 //Otherwise sets the third platform coordinate to 1000
 (*Game).platformX6[2] = 1000;
 }
 }else{
 //Otherwise sets the first and second platform coordinates to 1000
 (*Game).platformX6[1] = 1000;
 (*Game).platformX6[2] = 1000;
 }
}
/*
--movePlatformsIncrement Function--
The function increments the position of each platform by the distance passed in.
If the bottom platform is off the screen, move all rows one row down and
generate a new row.
Parameters:
 *Game - pointer to status struct
 distance - the distance the platforms need to move by
Sets:
 moves every row down by the distance
 creates a new row 7
~Vibhav Kaluvala
*/
void movePlatformsIncrement(status *Game, int distance){
 //Checks if the bottom platform is leaving the screen
 if((*Game).platformY0 > 230){
 //Increment for each possible platform
 for(int i = 0; i < 3; i++){
 //Moves the second row x coordinates to the first row x coordinates
 (*Game).platformX0[i] = (*Game).platformX1[i];
 }
 //Moves the second row y coordinate to the first row y coordinate
 (*Game).platformY0 = (*Game).platformY1;
 for(int i = 0; i < 3; i++){
 //Moves the third row x coordinates to the second row x coordinates
 (*Game).platformX1[i] = (*Game).platformX2[i];
 }
 //Moves the third row y coordinate to the second row y coordinate
 (*Game).platformY1 = (*Game).platformY2;
 for(int i = 0; i < 3; i++){
 //Moves the fourth row x coordinates to the third row x coordinates
 (*Game).platformX2[i] = (*Game).platformX3[i];
 }
 //Moves the fourth row y coordinates to the third row y coordinate
 (*Game).platformY2 = (*Game).platformY3;
 for(int i = 0; i < 3; i++){
 //Moves the fifth row x coordinates to the fourth row x coordinates
 (*Game).platformX3[i] = (*Game).platformX4[i];
 }
 //Moves the fifth row y coordinates to the fourth row y coordinate
 (*Game).platformY3 = (*Game).platformY4;
 for(int i = 0; i < 3; i++){
 //Moves the sixth row x coordinates to the fifth row x coordinates
 (*Game).platformX4[i] = (*Game).platformX5[i];
 }
 //Moves the sixth row y coordinate to the fifth row y coordinate
 (*Game).platformY4 = (*Game).platformY5;
 for(int i = 0; i < 3; i++){
 //Moves the seventh row x coordinates to the sixth row x coordinates
 (*Game).platformX5[i] = (*Game).platformX6[i];
 }
 //Moves the seventh row y coordinate to the sixth row y coordinate
 (*Game).platformY5 = (*Game).platformY6;
 //Sets the seventh row y coordinate to the sixth row y coordinate minus 50
 (*Game).platformY6 = (*Game).platformY6 - 50;
 //Generates the seventh row x coordinates
 generateNewRow(Game);
 }
 //Increments each rows y position by the distance
 (*Game).platformY0 += distance;
 (*Game).platformY1 += distance;
 (*Game).platformY2 += distance;
 (*Game).platformY3 += distance;
 (*Game).platformY4 += distance;
 (*Game).platformY5 += distance;
 (*Game).platformY6 += distance;
}
/*
--scrollDown Function--
The function increases the y position of all platforms
by the tuned scroll distance value. Also increases
the y position of the character by the scroll distance.
Parameters:
 *Game - pointer to status struct
Sets:
 moves every platform down by the scroll distance
 moves the character down by the scroll distance
~Vibhav Kaluvala
*/
void scrollDown(status *Game){
 int scrollDistance = 27;

 (*Game).platformY0 += scrollDistance;
 (*Game).platformY1 += scrollDistance;
 (*Game).platformY2 += scrollDistance;
 (*Game).platformY3 += scrollDistance;
 (*Game).platformY4 += scrollDistance;
 (*Game).platformY5 += scrollDistance;
 (*Game).platformY6 += scrollDistance;
 (*Game).coordinates[1] += scrollDistance;
}
/*
--backButton Function--
The function draws the back button at the top
right of the screen. Waits for the user to click
on the button to break out of the function.
Draws:
 draws the back button on the top right of the screen
~Luke Westerkamp
*/
void backButton(){
 //Sets the font color to black and draws a rectangle at the top right
 LCD.SetFontColor(BLACK);
 LCD.DrawRectangle(235, 5, 80, 30);
 //Writes the menu text centered in the box
 LCD.WriteAt("MENU", 250, 12);
 //Coordinates
 int x, y;
 //New boolean clicked set to false
 bool clicked = false;
 //While not clicked
 while(!clicked){
 // Wait for touch - use x and y
 while (!LCD.Touch(&x, &y)) {}
 // Touch - use x and y
 while (LCD.Touch(&x, &y)){}
 //If the user clicks in the top right
 if(x > 235 && y < 35){
 //Clear the screen
 LCD.Clear(ANTIQUEWHITE);
 //Set clicked to true
 clicked = true;
 }
 }
}
/*
--Stats class--
Class containing variables for stats and functions to
set and display stats
Contains:
 public function for displaying stats
 public function for setting stats
 public previous game score
 public session high score
 public previous time lasted
~Surya Suresh
*/
class Stats
{
 //Make everything public
 public:
 //Constructor
 Stats();
 //Function to display stats
 void displayStats();
 //Function to set stats
 void setStats(int score, float time);
 //Variables for previous score, session high score, and time lasted
 int prevScore;
 int sessionHigh;
 float timeLasted;
};
/*
--Stats constructor--
Constructor for setting default variable values
Sets:
 session high score to global max score
 previous score to global last score
 time lasted to global longest time
~Surya Suresh
*/
Stats::Stats(){
 sessionHigh = maxScore;
 prevScore = lastScore;
 timeLasted = longestTime;
}
/*
--Stats displayStats function--
The function draws all stats to the screen.
Used in the stats page in menu and after a game
is finished.
Draws:
 previous score to screen
 session high score to screen
 time lasted to screen
~Surya Suresh
*/
void Stats::displayStats(){
 //Clears screen and sets font color to black
 LCD.Clear(ANTIQUEWHITE);
 LCD.SetFontColor(BLACK);
 //Draws latest score to screen
 LCD.WriteAt("\tLatest Score: ", 0, 80);
 LCD.WriteAt(lastScore, 175, 80);
 //Draws session high score to screen
 LCD.WriteAt("\tSession High: ", 0, 110);
 LCD.WriteAt(maxScore, 175, 110);
 //Draws time lasted to screen
 LCD.WriteAt("\tTime Lasted (s): ", 0, 140);
 LCD.WriteAt(longestTime, 210, 140);
 //Calls backButton function
 backButton();
}
/*
--Stats setStats function--
Function sets the finished game score to
last score and the finished game time to
global variable longestTime. Checks if
finished game score is greater than session
high score.
Parameters:
 score - score from completed game
 time - time lasted from completed game
Sets:
 max score to score if score is greater than max score
 last score to score
 longest time to time
~Surya Suresh
*/
void Stats::setStats(int score, float time){
 //Checks if score is greater than max score
 if(score > maxScore){
 //Sets max score to score
 maxScore = score;
 }
 //Sets last score to score and longest time to time
 lastScore = score;
 longestTime = time;
}
/*
--VerticalMovement Function--
Moves the character up and down using kinematics. Once the
character has moved up and down, the character keeps falling
until it collides with a platform. If the character does not
collide with a platform the function returns false. The function
returns true otherwise.
Parameters:
 *Game - pointer to status struct
 left - if character is facing left
 gameStats - game stats class
Draws:
 animates the character moving up and down, and falling if
 it does not collide with a platform on the way down.
~Surya Suresh
*/
bool VerticalMovement(status *Game, bool left, Stats gameStats) {
 //Coordinates for user input
 int x, y;
 //Character coordinates taken from game struct
 int x1 = (*Game).coordinates[0], y1 = (*Game).coordinates[1];
 //Character fell boolean set to false
 bool fell = false;
 //Initial velocity set to 3
 float velocity = 3;
 //Upwards gravity multiplier set to 0.93 and downwards multiplier set to 0.95
 float gravityUp = 0.93, gravityDown = 0.95;
 //Set font color to black and write score on top left corner
 LCD.SetFontColor(BLACK);
 LCD.WriteAt(gameStats.prevScore, 5, 5);
 //Draw character
 player_sprite(x1, y1, (*Game).left);
 //Jump into the air
 while (y1 > (*Game).coordinates[1] - 45) {
 //Get mouse position
 while (LCD.Touch(&x, &y)) {}
 // Clear previous character
 LCD.SetFontColor(ANTIQUEWHITE);
 LCD.FillRectangle(x1, y1, FILLWIDTH, FILLHEIGHT);
 //Multiply velocity by upwards gravity and decrement character position
 velocity *= gravityUp;
 y1 -= velocity;
 //Clear all platforms
 clearAllPlatforms(Game);
 //Move all platforms by calculated velocity
 movePlatformsIncrement(Game, velocity);
 //Set font color to black and write score on top left corner
 LCD.SetFontColor(BLACK);
 LCD.WriteAt(gameStats.prevScore, 5, 5);
 //If user mouse is not too far to the right, set character x to mouse x
 if (x < 300) {
 x1 = x;
 }
 //Draw all platforms
 drawAllPlatforms(Game);
 //If the mouse x position is greater than the previous x position then the
character is facing right
 if(x > (*Game).prevX){
 //Draw a character facing right
 player_sprite(x1, y1, !(*Game).left);
 (*Game).prevLeft = false;
 //If the mouse x position is less than the previous x position then the
character is facing left
 }else if(x < (*Game).prevX){
 //Draw a character facing left
 player_sprite(x1, y1, (*Game).left);
 (*Game).prevLeft = true;

 //If the mouse x position is the same as the previous x position then the
character has not changed direction
 }else{
 //Draw a character facing the same direction
 player_sprite(x1, y1, (*Game).prevLeft);
 }

 //Sleep
 Sleep(.001);
 //Set previous x to x
 (*Game).prevX = x;
 //If the user is too high then stop moving upwards
 if(y1 < 5){
 break;
 }
 }
 //Fall back down
 while (y1 < (*Game).coordinates[1]) {
 //Get mouse position
 while (LCD.Touch(&x, &y)) {}
 //Clear previous character
 LCD.SetFontColor(ANTIQUEWHITE);
 LCD.FillRectangle(x1, y1, FILLWIDTH, FILLHEIGHT);
 //Divide velocity by upwards gravity and increment character position
 velocity /= gravityDown;
 y1 += velocity;
 //Draw all platforms
 drawAllPlatforms(Game);
 //Set font color to black and write score on top left corner
 LCD.SetFontColor(BLACK);
 LCD.WriteAt(gameStats.prevScore, 5, 5);
 //Check if the character is colliding with a platform
 if(checkCollision(x, y1, Game)){
 //Set the character y position to the current y position
 (*Game).coordinates[1] = y1;
 }
 //If user mouse is not too far to the right, set character x to mouse x
 if (x < 300) {
 x1 = x;
 }
 //If the mouse x position is greater than the previous x position then the
character is facing right
 if(x > (*Game).prevX){
 //Draw a character facing right
 player_sprite(x1, y1, !(*Game).left);
 (*Game).prevLeft = false;
 //If the mouse x position is less than the previous x position then the
character is facing left
 }else if(x < (*Game).prevX){
 //Draw a character facing left
 player_sprite(x1, y1, (*Game).left);
 (*Game).prevLeft = true;

 //If the mouse x position is the same as the previous x position then the
character has not changed direction
 }else{
 //Draw a character facing the same direction
 player_sprite(x1, y1, (*Game).prevLeft);
 }

 //Sleep
 Sleep(.001);
 //Set previous x to x
 (*Game).prevX = x;
 }
 //While there is no collision, the character is falling down
 while(!checkCollision(x1, y1, Game)){
 //While the character has not fallen too far
 while(y1 < 200){
 //Get mouse position
 while (LCD.Touch(&x, &y)) {}
 //Clear previous character
 LCD.SetFontColor(ANTIQUEWHITE);
 LCD.FillRectangle(x1, y1, FILLWIDTH, FILLHEIGHT);
 //Divide velocity by upwards gravity and increment character position
 velocity /= gravityDown;
 y1 += velocity;
 //If user mouse is not too far to the right, set character x to mouse x
 if (x < 300) {
 x1 = x;
 }
 //If the mouse x position is greater than the previous x position then
the character is facing right
 if(x > (*Game).prevX){
 //Draw a character facing right
 player_sprite(x1, y1, !(*Game).left);
 (*Game).prevLeft = false;
 //If the mouse x position is less than the previous x position then the
character is facing left
 }else if(x < (*Game).prevX){
 //Draw a character facing left
 player_sprite(x1, y1, (*Game).left);
 (*Game).prevLeft = true;

 //If the mouse x position is the same as the previous x position then
the character has not changed direction
 }else{
 //Draw a character facing the same direction
 player_sprite(x1, y1, (*Game).prevLeft);
 }
 //Sleep
 Sleep(.001);
 //Draw all platforms
 drawAllPlatforms(Game);
 //Break if the character has collided with a platform
 if(checkCollision(x1, y1, Game)){
 break;
 }

 }
 //If there has not been a collision
 if(!checkCollision(x1, y1, Game)){
 //The user fell
 fell = true;
 }

 //Break
 break;
 }
 //Clear previous character
 LCD.SetFontColor(ANTIQUEWHITE);
 LCD.FillRectangle(x1, y1, FILLWIDTH, FILLHEIGHT);
 LCD.Update();
 //Set character coordinates to updated coordinates
 (*Game).coordinates[0] = x;
 (*Game).coordinates[1] = y1;
 //Scroll screen
 scrollDown(Game);
 //Return fell
 return fell;
}
/*
--Play class--
Class containing variables for coordinates
and function for displaying the game
Contains:
 public function for displaying game
 private x1 coordinate
 private y1 coordinate
~Luke Westerkamp
*/
class Play
{
 //Public
 public:
 //Function to display game
 void displayPlay(Stats gameStats);
 //Private
 private:
 //Coordinates
 float x1, y1;
};
/*
--Play displayPlay function--
The function creates a new game struct and generates
initial platforms. It then starts a timer and runs
the game till the user falls. Once the game is finished
the timer stops and the stats are stored. The function
then displays actions for the user to take.
Parameters:
 gameStats - class for game stats
Runs:
 runs the game until the user falls, then asks the user to
 play again, view stats, or quit
~Luke Westerkamp
*/
void Play::displayPlay(Stats gameStats){
 //Clears the screen
 LCD.Clear(ANTIQUEWHITE);
 //Creates new status struct
 struct status Game;
 //Boolean for user fall set to false
 bool fell = false;
 //Generate initial platforms
 generateInitialPlatforms(&Game);
 //Starts timer
 float initialTime = TimeNow();
 //While the user hasn't fallen
 while(!fell){
 //Clear the screen
 LCD.Clear(ANTIQUEWHITE);
 //Draw all platforms
 drawAllPlatforms(&Game);
 //Call the vertical movement function and set equal to fell
 fell = VerticalMovement(&Game, Game.left, gameStats);
 //Update score by score constant
 gameStats.prevScore += SCORE;
 lastScore += SCORE;
 }
 //Stop timer
 float finalTime = TimeNow() - initialTime;
 //Update timer stats
 gameStats.timeLasted = finalTime;
 gameStats.setStats(gameStats.prevScore - 50, gameStats.timeLasted);
 //Clear screen and set font color to black
 LCD.Clear(ANTIQUEWHITE);
 LCD.SetFontColor(BLACK);
 //Display game over
 LCD.WriteAt("GAME OVER!", 105, 30);
 //Create two buttons for play again and view stats
 LCD.DrawRectangle(40, 70, 240, 30);
 LCD.DrawRectangle(40, 110, 240, 30);
 LCD.WriteAt("Play Again", 100, 77);
 LCD.WriteAt("View Stats", 100, 117);
 //Write that user can click anywhere to quit
 LCD.WriteAt("Click Anywhere To Quit", 30, 177);
 //Coordinates
 int x, y;
 //Wait for user to click
 while(!LCD.Touch(&x, &y)){}
 while(LCD.Touch(&x, &y)){}

 //Check if user clicked within x bounds of button
 if (x > 40 && x < 280)
 {
 //Check if user clicked on play again
 if (y < 100 && y > 70)
 {
 //Set previous score to 0 and play game again
 gameStats.prevScore = 0;
 displayPlay(gameStats);
 }
 //Check if user clicked on display stats
 if (y < 140 && y > 110)
 {
 //Display stats
 gameStats.displayStats();
 }
 }
}
/*
--Credits Function--
The function draws the credits to the screen.
Draws the names of developers as well as references used.
Draws:
 each team members name indented under developer label
 FEH Proteus Guide indented under reference label
 back button to take the user to the menu
~Luke Westerkamp
*/
void Credits()
{
 //Clears screen and sets font color to black
 LCD.Clear(ANTIQUEWHITE);
 LCD.SetFontColor(BLACK);
 //Draws names to screen
 LCD.WriteAt("\tDevelopers: ", 0, 30);
 LCD.WriteAt("\t\tVibhav Kaluvala", 0, 60);
 LCD.WriteAt("\t\tSurya Suresh", 0, 90);
 LCD.WriteAt("\t\tLuke Westerkamp", 0, 120);
 //Draws references to screen
 LCD.WriteAt("\tReferences: ", 0, 150);
 LCD.WriteAt("\t\tFEH Proteus Guide", 0, 180);
 //Calls back button function
 backButton();
}
/*
--Instructions Function--
The function draws the instructions to the screen.
Draws:
 instructions of game
 back button to take the user to the menu
~Luke Westerkamp
*/
void Instructions()
{
 //Clears screen and sets font color to black
 LCD.Clear(ANTIQUEWHITE);
 LCD.SetFontColor(BLACK);
 //Draws instructions to screen
 LCD.WriteAt("\tMove the cursor from", 0, 50);
 LCD.WriteAt("\tside to side to move", 0, 70);
 LCD.WriteAt("\tthe character. Continue", 0, 90);
 LCD.WriteAt("\tupwards to increase your", 0, 110);
 LCD.WriteAt("\tscore.", 0, 130);
 //Calls back button function
 backButton();
}
/*
--DrawMenu Function--
The function draws the menu to the screen.
Draws four boxes with labels and waits for the user
to click on of them. When the user clicks on a box
the appropriate screen is displayed.
Parameters:
 gameStats - class for game stats
 gamePlay - class for playing game
Draws:
 game title
 buttons for:
 play
 instructions
 stats
 credits
~Luke Westerkamp
*/
void DrawMenu(Stats gameStats, Play gamePlay)
{
 //Clears screen and sets font color to black
 LCD.SetBackgroundColor(ANTIQUEWHITE);
 LCD.SetFontColor(BLACK);
 //Draws title to screen
 LCD.WriteAt("DOODLE JUMP--", 80, 30);
 //Draws rectangles for buttons to screen
 LCD.DrawRectangle(40, 70, 240, 30);
 LCD.DrawRectangle(40, 110, 240, 30);
 LCD.DrawRectangle(40, 150, 240, 30);
 LCD.DrawRectangle(40, 190, 240, 30);
 //Draws text for buttons to screen
 LCD.WriteAt("Play", 135, 77);
 LCD.WriteAt("Instructions", 90, 117);
 LCD.WriteAt("Stats", 130, 157);
 LCD.WriteAt("Credits", 120, 197);
 //Coordinates
 int x, y;
 // Wait for touch - use x and y
 while (!LCD.Touch(&x, &y)) {}
 // Touch - use x and y
 while (LCD.Touch(&x, &y)){}
 //Check if user clicked within x bounds of buttons
 if (x > 40 && x < 280)
 {
 //Check if user clicked play
 if (y < 100 && y > 70)
 {
 //Display play
 gamePlay.displayPlay(gameStats);
 }
 //Check if user clicked instructions
 if (y < 140 && y > 110)
 {
 //Display instructions
 Instructions();
 }
 //Check is user clicked stats
 if (y < 180 && y > 150)
 {
 //Display stats
 gameStats.displayStats();
 }
 //Check is user clicked credits
 if (y < 220 && y > 190)
 {
 //Display credits
 Credits();
 }
 }
 //Clear screen
 LCD.Clear(ANTIQUEWHITE);
}
/*
--main Function--
The function sets the background color and creates
the stats and play classes. The function then calls
the DrawMenu function.
~Vibhav Kaluvala, Surya Suresh, Luke Westerkamp
*/
int main()
{
 //Clear screen
 LCD.SetBackgroundColor(ANTIQUEWHITE);
 LCD.Clear(ANTIQUEWHITE);
 //Create new instance of stats class and play class
 Stats gameStats;
 Play gamePlay;
 while (1)
 {
 //Draw menu
 DrawMenu(gameStats, gamePlay);
 LCD.Update();
 // Never end
 }
}