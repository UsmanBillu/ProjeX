#include<iostream>
#include<windows.h>
#include"help.h"
#include<fstream>
using namespace std;
int aliens;
const int ALIEN_WIDTH = 6;   // Width of the alien, including arms and body
const int ALIEN_HEIGHT = 16; // Height of the alien, including arms and eyes
const int SPACING = 70;        // Spacing between rows and columns (in pixels)
bool condition = false;
bool looser = false;
bool extremeloop = true;
bool scoreboardclear = false;//after loosing clearing aliens left of console
char s[10];
int score = 0;
int alienkill = 0;
int life = 3;
int high[5] = { 0 };
int h1, h2, h3, h4, h5;
char hs1[10], hs2[10], hs3[10], hs4[10], hs5[10];
int displayhighscores[5] = { 0 };
bool game = false;
int speed;// DIFFICULTY 
int alienmode;// ALIEN STYLE
bool menu = true;
//SAVING AND LOADING
bool death[11][5]; float X[11][5]; float Y[11][5];
void drawAlien(int startX, int startY) {
    myLine(startX + 1450, startY + 70, startX + 1520, startY + 40, 255, 0, 0);// Alien's Upper Red Arm
    myLine(startX + 1450, startY + 70, startX + 1520, startY + 100, 255, 0, 0);// Alien's Lower Red Arm
    myLine(startX + 1450, startY + 50, startX + 1450, startY + 90, 0, 0, 255);// Alien's Front Blue Line
    myEllipse(startX + 1500, startY + 55, startX + 1520, startY + 65, 0, 255, 0);// Alien's Upper Green Eye
    myEllipse(startX + 1500, startY + 75, startX + 1520, startY + 85, 0, 255, 0);// Alien's Lower Green Eye
}
void eraseAlien(int startX, int startY) {
    drawAlien(startX, startY);
    myLine(startX + 1450, startY + 70, startX + 1520, startY + 40, 0, 0, 0); // Black Upper Arm
    myLine(startX + 1450, startY + 70, startX + 1520, startY + 100, 0, 0, 0); // Black Lower Arm
    myLine(startX + 1450, startY + 50, startX + 1450, startY + 90, 0, 0, 0); // Black Blue Line
    myEllipse(startX + 1500, startY + 55, startX + 1520, startY + 65, 0, 0, 0); // Black Upper Eye
    myEllipse(startX + 1500, startY + 75, startX + 1520, startY + 85, 0, 0, 0); // Black Lower Eye
}
void findhighscore(int arr[], int s, int score) {
    ifstream mydata;
    mydata.open("highscores.txt");
    int i = 0; int n;
    while (mydata >> n) {
        arr[i++] = n;
    }
    mydata.close();
    for (int i = 0; i < 5 - 1; i++) {
        for (int j = 0; j < 5 - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = high[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    if (score > arr[4]) {
        arr[4] = score;
    }
    ofstream myfile;
    myfile.open("highscores.txt");
    for (int i = 0; i < 5; i++) {
        myfile << arr[i] << endl;
    }
    myfile.close();
}
void readinghighscore(int arr[], int s) {
    ifstream mysavedscores;
    mysavedscores.open("highscores.txt");
    int i = 0; int n;
    while (mysavedscores >> n) {
        arr[i++] = n;
    }
    mysavedscores.close();
    for (int i = 0; i < 5 - 1; i++) {
        for (int j = 0; j < 5 - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void numbertochararray(int n, char score[]) {
    int index = 0;
    do
    {
        score[index++] = (n % 10) + '0';
        n = n / 10;
    } while (n > 0);
    score[index] = '\0';
    for (int i = 0; i < index / 2; ++i) {
        char temp = score[i];
        score[i] = score[index - i - 1];
        score[index - i - 1] = temp;
    }
}
void lives(int& life)
{
    ofstream live("lives.txt");
    live << life;
    live.close();
}
void dead(bool death[11][5])
{
    ofstream kill("dead coordinates.txt");
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i != 4)
            {
                kill << death[j][i] << ' ';

            }

            else kill << death[j][i] << ' ';

        }
        kill << endl;

    }

    kill.close();
}
void readdead(bool death[11][5])
{
    ifstream kill("dead coordinates.txt");
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i != 4)
            {
                kill >> death[j][i];

            }

            else kill >> death[j][i];

        }


    }

    kill.close();
}
void readlives(int& life)
{
    ifstream live("lives.txt");
    live >> life;
    live.close();
}
void savecordinatesaliens(float X[11][5], float Y[11][5]) {
    ofstream alien("alien coordinates.txt");
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i != 4)
            {
                alien << X[j][i] << ' ';

            }

            else alien << X[j][i] << ' ';

        }
        alien << endl;

    }
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i != 4)
                alien << Y[j][i] << ' ';
            else
                alien << Y[j][i] << ' ';

        }
        alien << endl;

    }
    alien.close();
}
void returnalien(float X[11][5], float Y[11][5])
{
    ifstream alien("alien coordinates.txt");
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i != 4)
            {
                alien >> X[j][i];

            }
            else alien >> X[j][i];
        }


    }
    for (int j = 0; j < 11; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i != 4)
                alien >> Y[j][i];
            else
                alien >> Y[j][i];
        }

    }
    alien.close();
}
int main() {
    while (extremeloop) {
        while (menu) {
            if (scoreboardclear) {
                system("cls");
                scoreboardclear = false;
            }
            int choice; score = 0; alienkill = 0; life = 3;
            drawText(60, 520, 110, 0, 255, 0, "MADNI INVADERS");
            myRect(520, 300, 1350, 400, 255, 0, 0);
            drawText(30, 710, 310, 0, 255, 255, "P TO PLAY GAME");
            myRect(520, 410, 1350, 510, 255, 0, 0);
            drawText(30, 710, 420, 0, 255, 255, "H HIGH SCORES");
            myRect(520, 520, 1350, 620, 255, 0, 0);
            drawText(30, 710, 530, 0, 255, 255, "E TO EXIT GAME");
            drawText(20, 790, 670, 204, 255, 0, "A PROJECT BY");
            drawText(20, 720, 720, 255, 0, 0, "HELLO WORLD HACKERS");
            drawText(20, 810, 770, 204, 255, 0, "DEVELOPERS");
            drawText(20, 750, 820, 255, 0, 0, "MUSTAFA X USMAN");
            drawText(20, 720, 870, 0, 255, 255, "ALL RIGHTS RESERVED");
            bool keypressed = isKeyPressed(choice);
            if (keypressed) {
                if (choice == 9) {//P IS PRESSED TO START MADNI INVADERS
                    bool check1 = true; // alien type while loop
                    bool check = true;//  difficulty level while loop
                    score = 0; alienkill = 0; life = 3;
                    system("cls");
                    while (check1) {
                        drawText(50, 660, 110, 255, 0, 0, "ALIENS TYPE");
                        myRect(630, 300, 1250, 400, 0, 0, 255);
                        drawText(40, 730, 310, 0, 255, 0, "1 FOR RATS");
                        myRect(630, 410, 1250, 510, 0, 0, 255);
                        drawText(40, 730, 420, 0, 255, 0, "2 FOR SNAKES");
                        drawText(20, 685, 600, 255, 0, 0, "ESC TO GO BACK TO MAIN MENU");
                        bool keypressed = isKeyPressed(choice);
                        if (keypressed) {
                            if (choice == 7) {//ESC PRESSED TO BACK
                                check1 = false;
                                check = false;
                                system("cls");
                            }
                            if (choice == 16) {//1 PRESSED FOR RATS
                                aliens = 1;
                                check1 = false;
                            }
                            if (choice == 17) {//2 PRESSES FOR SNAKES
                                aliens = 2;
                                check1 = false;
                            }
                        }
                    }
                    system("cls");
                    while (check) {
                        drawText(60, 450, 110, 0, 255, 0, "DIFFICULTY LEVEL");
                        myRect(550, 300, 1250, 400, 0, 0, 255);
                        drawText(40, 730, 310, 255, 0, 0, "1 EASY");
                        myRect(550, 410, 1250, 510, 0, 0, 255);
                        drawText(40, 730, 420, 255, 0, 0, "2 MEDIUM");
                        myRect(550, 520, 1250, 620, 0, 0, 255);
                        drawText(40, 730, 530, 255, 0, 0, "3 HARD");
                        drawText(20, 625, 700, 255, 0, 0, "ESC TO GO BACK TO MAIN MENU");
                        bool keypressed = isKeyPressed(choice);
                        if (keypressed) {
                            if (choice == 7) {//ESC PRESSED TO BACK
                                check = false;
                                system("cls");
                            }
                            if (choice == 16) {// 1 PRESSED FOR EASY MODE
                                speed = 1;
                                game = true;
                                menu = false;
                                check = false;
                            }
                            if (choice == 17) {// 2 PRESSED FOR EASY MODE
                                speed = 2;
                                game = true;
                                menu = false;
                                check = false;
                            }
                            if (choice == 18) {// 3 PRESSED FOR EASY MODE
                                speed = 3;
                                game = true;
                                menu = false;
                                check = false;
                            }
                        }
                    }
                }
                if (choice == 11) {//   E PRESSED to exit the game
                    game = false;
                    menu = false;
                    extremeloop = false;
                    system("cls");
                }
                if (choice == 13) {//   H IS PRESSED TO SHOW 5 PREVIOUS HIGH SCORES IN ORDER
                    //PRINTING HEADINGS
                    system("cls");
                    bool highestmenu = true;
                    while (highestmenu) {
                        readinghighscore(displayhighscores, 5);
                        //converting in variables so that we can display them using provides help.h drawText function()!
                        h1 = displayhighscores[0], h2 = displayhighscores[1], h3 = displayhighscores[2], h4 = displayhighscores[3], h5 = displayhighscores[4];
                        // storing ends here
                        drawText(60, 500, 110, 0, 255, 255, "HIGHEST SCORES");
                        drawText(40, 500, 310, 204, 255, 0, "1ST HIGHEST SCORE");
                        drawText(40, 500, 420, 204, 255, 0, "2ND HIGHEST SCORE");
                        drawText(40, 500, 530, 204, 255, 0, "3RD HIGHEST SCORE");
                        drawText(40, 500, 640, 204, 255, 0, "4TH HIGHEST SCORE");
                        drawText(40, 500, 750, 204, 255, 0, "5TH HIGHEST SCORE");
                        drawText(40, 1260, 10, 0, 0, 0, hs1);
                        numbertochararray(h1, hs1);
                        drawText(40, 1260, 310, 255, 0, 0, hs1);//PRINTING SCORE 1
                        drawText(40, 1260, 10, 0, 0, 0, hs2);
                        numbertochararray(h2, hs2);
                        drawText(40, 1260, 420, 255, 0, 0, hs2);//PRINTING SCORE 2
                        drawText(40, 1260, 10, 0, 0, 0, hs3);
                        numbertochararray(h3, hs3);
                        drawText(40, 1260, 530, 255, 0, 0, hs3);//PRINTING SCORE 3
                        drawText(40, 1260, 10, 0, 0, 0, hs4);
                        numbertochararray(h4, hs4);
                        drawText(40, 1260, 640, 255, 0, 0, hs4);//PRINTING SCORE 4
                        drawText(40, 1260, 10, 0, 0, 0, hs5);
                        numbertochararray(h5, hs5);
                        drawText(40, 1260, 750, 255, 0, 0, hs5);//PRINTING SCORE 5
                        //functioning for escaping the to main menu from this highscoring pages
                        drawText(20, 550, 900, 255, 0, 0, "PRESS ESC TO GO BACK TO MAIN MENU");
                        bool keypressed = isKeyPressed(choice);
                        if (keypressed) {
                            if (choice == 7) {// ESC IS PRESSED
                                highestmenu = false;
                                system("cls");
                            }
                        }
                    }
                }
            }
        }
        if (game) {
            system("cls");
        }
        bool check1 = true; bool check2 = true; // checks for menu after winning or loosing
        int whichkey;
        int gridStartX = 10;  // Starting X coordinate for the grid
        int gridStartY = 2;   // Starting Y coordinate for the grid
        int rows = 11; int cols = 5;
        int count = -1;
        float bullet_X[1000] = { -1 }; float bullet_Y[1000] = { -1 };
        float X[11][5]; float Y[11][5];//ARRAYS FOR MOVING ALIENS 
        float startX = 50; float startY = 500;
        bool death[11][5];
        // DRAWING MADNI JET
        myRect(startX, startY, startX + 100, startY + 60, 0, 255, 0, 0, 255); //main rect
        myLine(startX + 25, startY + 60, startX + 25, startY + 100, 0, 255, 0);//down straight line
        myLine(startX + 25, startY + 100, startX + 55, startY + 60, 0, 255, 0);//downward diagonal
        myLine(startX + 25, startY - 40, startX + 55, startY, 0, 255, 0);// up ward diagonal
        myLine(startX + 25, startY, startX + 25, startY - 40, 0, 255, 0);//up straight line
        //DRAWING ALIENS 
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                X[row][col] = gridStartX + col * (ALIEN_WIDTH + SPACING);
                Y[row][col] = gridStartY + row * (ALIEN_HEIGHT + SPACING);
                if (row == 0) {
                    death[row][col] = false;
                    eraseAlien(X[row][col], Y[row][col]);
                }
                else {
                    death[row][col] = true;
                    drawAlien(X[row][col], Y[row][col]);
                }
            }
        }
        while (game) {
            // SCORE BOARD 
            if (life == 0) {//  game loss condition
                system("cls");
                findhighscore(high, 5, score);
                bool check1 = true;
                while (check1) {
                    int choice;
                    drawText(60, 700, 350, 255, 0, 0, "GAMEOVER");
                    myRect(500, 500, 1400, 600, 0, 0, 255);
                    drawText(40, 670, 510, 0, 255, 0, "M TO OPEN MENU");
                    bool keypressed = isKeyPressed(choice);
                    if (keypressed) {
                        if (choice == 10) {//opening menuuuu
                            game = false;
                            check1 = false;
                            menu = true;
                            scoreboardclear = true;
                            system("cls");
                        }
                    }
                }
            }
            drawText(40, 20, 10, 0, 255, 0, "SCORE");//score
            drawText(40, 250, 10, 0, 0, 0, s);//black
            numbertochararray(score, s);//coversion
            drawText(40, 250, 10, 0, 255, 0, s);//color
            int displayhighestscore;
            readinghighscore(high, 5);
            displayhighestscore = high[0];
            drawText(40, 405, 10, 255, 0, 0, "HIGH SCORE");//highscore
            drawText(40, 810, 10, 0, 0, 0, hs1);//black
            numbertochararray(displayhighestscore, hs1);//conversion
            drawText(40, 810, 10, 0, 255, 0, hs1);//color
            drawText(40, 1000, 10, 0, 255, 255, "LIVES");
            myLine(0, 100, 1900, 100, 255, 0, 0);//line of score card
            myEllipse(1250, 5, 1340, 95, 0, 0, 0, 0);
            myEllipse(1350, 5, 1440, 95, 0, 0, 0, 0);
            myEllipse(1450, 5, 1540, 95, 0, 0, 0, 0);
            if (life == 3) {
                myEllipse(1250, 5, 1340, 95, 255, 0, 0, 255);
                myEllipse(1350, 5, 1440, 95, 255, 0, 0, 255);
                myEllipse(1450, 5, 1540, 95, 255, 0, 0, 255);
            }
            else  if (life == 2) {
                myEllipse(1250, 5, 1340, 95, 255, 0, 0, 255);
                myEllipse(1350, 5, 1440, 95, 255, 0, 0, 255);
                myEllipse(1450, 5, 1540, 95, 0, 0, 0, 0);
            }
            else   if (life == 1) {
                myEllipse(1250, 5, 1340, 95, 255, 0, 0, 255);
                myEllipse(1350, 5, 1440, 95, 0, 0, 0, 0);
                myEllipse(1450, 5, 1540, 95, 0, 0, 0, 0);
            }
            // SCORE GRAPHICS 
            bool keypressed = isKeyPressed(whichkey);
            //SNAKES codes
            if (aliens == 2) {
                for (int row = 0; row < rows; ++row) {
                    for (int col = 4; col < cols; ++col) {
                        eraseAlien(X[row][col], Y[row][col]);

                    }
                }
                for (int row = 0; row < rows; ++row) {
                    for (int col = 0; col < cols; ++col) {
                        if (death[row][col]) {

                            X[row][col] -= 1; // Move alien left by 10 pixels

                            drawAlien(X[row][col], Y[row][col]);
                        }
                    }
                }

            }
            //  SNAKES CODE 
            //FOR RATS
            if (aliens == 1) {
                for (int row = 0; row < rows; ++row) {
                    for (int col = 0; col < cols; ++col) {
                        if (death[row][col]) {
                            eraseAlien(X[row][col], Y[row][col]);
                            if (speed == 1) {
                                X[row][col] -= 2;
                            }
                            else   if (speed == 2) {
                                X[row][col] -= 6;
                            }
                            else   if (speed == 3) {
                                X[row][col] -= 8;
                            }
                            drawAlien(X[row][col], Y[row][col]);
                        } // Move alien left by 10 

                        if (startX >= X[row][col] + 1340 && startX <= X[row][col] + 1520 && startY >= Y[row][col] + 30 && startY <= Y[row][col] + 90 || X[row][col] <= -1450) {
                            //coditions for resetting the screen
                            life--;

                            if (life == 0) {
                                break;
                            }
                            for (int row = 0; row < rows; ++row) {
                                for (int col = 0; col < cols; ++col) {
                                    if (death[row][col]) {
                                        eraseAlien(X[row][col], Y[row][col]);
                                    }
                                }
                            }
                            for (int row = 0; row < rows; ++row) {
                                for (int col = 0; col < cols; ++col) {
                                    X[row][col] = gridStartX + col * (ALIEN_WIDTH + SPACING);
                                    Y[row][col] = gridStartY + row * (ALIEN_HEIGHT + SPACING);
                                    if (death[row][col] == false) {

                                        eraseAlien(X[row][col], Y[row][col]);
                                    }
                                    else {

                                        drawAlien(X[row][col], Y[row][col]);
                                    }
                                }
                            }
                        }
                        //RATS CODE 
                        if (life == 0) {
                            break;
                        }
                    }
                    if (life == 0) {
                        break;
                    }
                }
                if (life == 0) {
                    break;
                }
            }

            for (int i = 0; i < count; i++)
            {
                if (bullet_X[i] != -1 && bullet_Y[i] != -1)
                {
                    // Erase the bullet at the old position
                    myRect(bullet_X[i], bullet_Y[i], bullet_X[i] + 20, bullet_Y[i] + 2, 0, 0, 0, 0, 0, 0);

                    // Update bullet position
                    bullet_X[i] += 70;  // Increased speed for visibility
                    // Check if the bullet has gone off the screen
                    if (bullet_X[i] > 1900)
                    {
                        bullet_X[i] = -1; // Mark as inactive
                        bullet_Y[i] = -1;
                    }
                    else
                    {
                        // Draw the bullet at the new position
                        myRect(bullet_X[i], bullet_Y[i], bullet_X[i] + 20, bullet_Y[i] + 2, 0, 0, 255, 0, 255, 0);
                        for (int row = 0; row <= rows; ++row) {
                            for (int col = 0; col <= cols; ++col) {
                                if (death[row][col] && bullet_X[i] >= X[row][col] + 1450 && bullet_X[i] <= X[row][col] + 1520 && bullet_Y[i] >= Y[row][col] + 50 && bullet_Y[i] <= Y[row][col] + 90) {
                                    eraseAlien(X[row][col], Y[row][col]);
                                    alienkill++;
                                    if (speed == 1) {
                                        score += 10;
                                    }
                                    else if (speed == 2) {
                                        score += 20;
                                    }
                                    else if (speed == 3) {
                                        score += 30;
                                    }
                                    death[row][col] = false; myRect(bullet_X[i], bullet_Y[i], bullet_X[i] + 20, bullet_Y[i] + 2, 0, 0, 0, 0, 0, 0);
                                    bullet_X[i] = -1; bullet_Y[i] = -1; break;
                                }
                            }
                        }
                        if (bullet_X[i] != -1 && bullet_Y[i] != -1) {
                            myRect(bullet_X[i], bullet_Y[i], bullet_X[i] + 20, bullet_Y[i] + 2, 0, 0, 255, 0, 255, 0);
                        }
                    }
                }
            }
            //here we just checking for keys
            if (keypressed) {//left movement mechanism
                if (whichkey == 1) {
                    if (startX - 15 > 0) {
                        myRect(startX, startY, startX + 100, startY + 60, 0, 0, 0);
                        myLine(startX + 25, startY + 60, startX + 25, startY + 100, 0, 0, 0);
                        myLine(startX + 25, startY + 100, startX + 55, startY + 60, 0, 0, 0);
                        myLine(startX + 25, startY - 40, startX + 55, startY, 0, 0, 0);
                        myLine(startX + 25, startY, startX + 25, startY - 40, 0, 0, 0);
                        startX -= 15;
                        myRect(startX, startY, startX + 100, startY + 60, 0, 255, 0, 0, 255, 0);
                        myLine(startX + 25, startY + 60, startX + 25, startY + 100, 0, 255, 0);
                        myLine(startX + 25, startY + 100, startX + 55, startY + 60, 0, 255, 0);
                        myLine(startX + 25, startY - 40, startX + 55, startY, 0, 255, 0);
                        myLine(startX + 25, startY, startX + 25, startY - 40, 0, 255, 0);
                    }
                }
                if (whichkey == 2) {    //up movement
                    if (startY - 15 > 120) {
                        myRect(startX, startY, startX + 100, startY + 60, 0, 0, 0);
                        myLine(startX + 25, startY + 60, startX + 25, startY + 100, 0, 0, 0);
                        myLine(startX + 25, startY + 100, startX + 55, startY + 60, 0, 0, 0);
                        myLine(startX + 25, startY - 40, startX + 55, startY, 0, 0, 0);
                        myLine(startX + 25, startY, startX + 25, startY - 40, 0, 0, 0);
                        startY -= 15;
                        myRect(startX, startY, startX + 100, startY + 60, 0, 255, 0, 0, 255, 0);
                        myLine(startX + 25, startY + 60, startX + 25, startY + 100, 0, 255, 0);
                        myLine(startX + 25, startY + 100, startX + 55, startY + 60, 0, 255, 0);
                        myLine(startX + 25, startY - 40, startX + 55, startY, 0, 255, 0);
                        myLine(startX + 25, startY, startX + 25, startY - 40, 0, 255, 0);
                    }
                }
                if (whichkey == 3) {    //right movement
                    if (startX + 15 < 300) {
                        myRect(startX, startY, startX + 100, startY + 60, 0, 0, 0);
                        myLine(startX + 25, startY + 60, startX + 25, startY + 100, 0, 0, 0);
                        myLine(startX + 25, startY + 100, startX + 55, startY + 60, 0, 0, 0);
                        myLine(startX + 25, startY - 40, startX + 55, startY, 0, 0, 0);
                        myLine(startX + 25, startY, startX + 25, startY - 40, 0, 0, 0);
                        startX += 15;
                        myRect(startX, startY, startX + 100, startY + 60, 0, 255, 0, 0, 255, 0);
                        myLine(startX + 25, startY + 60, startX + 25, startY + 100, 0, 255, 0);
                        myLine(startX + 25, startY + 100, startX + 55, startY + 60, 0, 255, 0);
                        myLine(startX + 25, startY - 40, startX + 55, startY, 0, 255, 0);
                        myLine(startX + 25, startY, startX + 25, startY - 40, 0, 255, 0);
                    }
                }
                if (whichkey == 4) {
                    if (startY + 15 <= 920) {     //downward movement
                        myRect(startX, startY, startX + 100, startY + 60, 0, 0, 0);
                        myLine(startX + 25, startY + 60, startX + 25, startY + 100, 0, 0, 0);
                        myLine(startX + 25, startY + 100, startX + 55, startY + 60, 0, 0, 0);
                        myLine(startX + 25, startY - 40, startX + 55, startY, 0, 0, 0);
                        myLine(startX + 25, startY, startX + 25, startY - 40, 0, 0, 0);
                        startY += 15;
                        myRect(startX, startY, startX + 100, startY + 60, 0, 255, 0, 0, 255, 0);
                        myLine(startX + 25, startY + 60, startX + 25, startY + 100, 0, 255, 0);
                        myLine(startX + 25, startY + 100, startX + 55, startY + 60, 0, 255, 0);
                        myLine(startX + 25, startY - 40, startX + 55, startY, 0, 255, 0);
                        myLine(startX + 25, startY, startX + 25, startY - 40, 0, 255, 0);
                    }
                }
                if (whichkey == 8) {    //shift for bullet firing
                    count++;
                    bullet_X[count] = startX + 100;
                    bullet_Y[count] = startY + 30;
                }
                if (whichkey == 9 || whichkey == 7) {//esc or p
                    bool pauseflag = true;
                    system("cls");
                    while (pauseflag) {
                        drawText(60, 750, 150, 255, 0, 0, "PAUSED");
                        myRect(620, 390, 1240, 470, 0, 0, 255);
                        drawText(30, 630, 400, 0, 255, 0, "PRESS S TO SAVE GAME");
                        myRect(620, 490, 1240, 570, 0, 0, 255);
                        drawText(30, 630, 500, 0, 255, 0, "PRESS L TO LOAD GAME");
                        myRect(620, 590, 1240, 670, 0, 0, 255);
                        drawText(30, 630, 600, 0, 255, 0, "M BACK TO MAIN MENU");
                        drawText(20, 725, 800, 255, 0, 0, "PRESS ESC TO RESUME");

                        bool keypressed = isKeyPressed(whichkey);
                        if (keypressed) {
                            if (whichkey == 14) {// s is pressed for saving game
                                dead(death);
                                lives(life);//FOR SAVING LIFES
                                savecordinatesaliens(X, Y);//FOR SAVING GRID COORDINATES
                                //SAVING SCORE AND DIFFICULTY LVL
                                ofstream myscore;
                                myscore.open("scores.txt");
                                myscore << score << endl;
                                myscore << speed << endl;
                                myscore << alienkill << endl;
                                myscore.close();
                                //SAVING SCORE AND DIFFICULTY LVL ENDS UP HERE
                                drawText(20, 10, 0, 255, 0, 0, "SAVED SUCCESSFULLY");
                            }
                            if (whichkey == 9 || whichkey == 7) {//resuming again with p or esc
                                pauseflag = false;
                                system("cls");
                            }
                            if (whichkey == 10) {// M PRESSED TO GO BACK TO MAIN MENU
                                game = false;
                                pauseflag = false;
                                menu = true;
                                findhighscore(high, 5, score);
                                system("cls");
                            }
                            if (whichkey == 15)//L IS PRESSED FOR LOADING GAME
                            {
                                //LOADING SAVED SCORE AND DIFFICULTY LVL
                                ifstream myscore;
                                myscore.open("scores.txt");
                                myscore >> score;
                                myscore >> speed;
                                myscore >> alienkill;
                                myscore.close();
                                //LOADING SAVED SCORE AND DIFFICULTY LVL ENDS UP HERE

                                system("cls");
                                for (int row = 0; row < rows; ++row) {
                                    for (int col = 0; col < cols; ++col) {

                                        eraseAlien(X[row][col], Y[row][col]);
                                    }
                                }
                                readdead(death);
                                readlives(life);
                                returnalien(X, Y);
                                pauseflag = false;
                            }

                        }
                    }
                }
            }
            //HERE YOU WIN THE GAME
            if (life != 0 && alienkill == 50) {
                system("cls");
                findhighscore(high, 5, score);
                bool check2 = true;
                while (check2) {
                    drawText(60, 700, 350, 0, 255, 0, "YOU WIN");
                    myRect(500, 500, 1400, 600, 0, 0, 255);
                    drawText(40, 670, 510, 255, 0, 0, "M TO OPEN MENU");
                    int choice;
                    bool keypressed = isKeyPressed(choice);
                    if (keypressed) {
                        if (choice == 10) {//opeing menuuu
                            game = false;
                            check2 = false;
                            menu = true;
                            system("cls");
                        }
                    }
                }
            }
        }
    }
    return 0;
}