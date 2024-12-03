#include<iostream>
#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>

using namespace std;

#define MAX_LENGTH 1000

//directions
const char DIR_UP = "U";
const char DIR_DOWN = "D";
const char DIR_LEFT = "L";
const char DIR_RIGHT = "R";

int consoleWidth, consoleHeight;

void initScreen(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

struct Point {
    int xCord, yCord;
    Point(){  
    }
    Point(int x, int y){
        xCord = x;
        yCord = y;
    }
};

class Snake {
    int length;
    char direction;

public:
    Point body[MAX_LENGTH];
    Snake(int x,int y){
        length = 1;
        body[0] = Point(x,y);
        direction = DIR_RIGHT;
    }

    int getLength(){
        return length;
    }

    void changeDirection(char newDirection){
        if(newDirection == DIR_UP && !direction == DIR_DOWN) direction = newDirection;

        else if(newDirection == DIR_DOWN && !direction == DIR_UP) direction = newDirection;

        else if(newDirection == DIR_LEFT && !direction == DIR_RIGHT) direction = newDirection;

        else if(newDirection == DIR_RIGHT && !direction == DIR_LEFT) direction = newDirection;
    }

    bool move(Point food){
        for(int i-length-1 ; i > 0; i--){
            body[i] = body[i-1];
        }

        switch(direction){
            case DIR_UP:
                body[0].yCord--;
                break;
            case DIR_DOWN:
                body[0].yCord++;
                break;
            case DIR_LEFT:
                body[0].xCord--;
                break;
            case DIR_RIGHT:
                body[0].xCord++;
                break;
        }

        //snake bites itself
        for(int i=0 ; i<length ; i++){
            if(body[0].xCord == body[i].xCord && body[0].yCord == body[i].yCord) return false;
        }

        //snake eats food
        if(body[0].xCord == food.xCord && body[0].yCord == food.yCord){
            body[length] = Point(body[length-1].xCoord,body[length-1].yCoord);
            length++;
            score++;
        }
    }
};

class Board {
    Snake *snake;
    const char SNAKE_BODY = 'o';
    Point food;
    const char FOOD = 'o';
    int score;

public:
    Board(){
        spawnFood();
        snake = new Snake(10,10);
        score = 0;
    }
    ~Board(){
        delete snake;
    }

    int getScore(){
        return score;
    }

    void spawnFood(){
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;
        food = Point(x,y);
    }

    void gotoxy(int x , int y){
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    void draw(){
        system("cls");
        for(int i = 0 ; i < snake -> getLength() ; i++){
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }

        gotoxy(food.xCord, food.yCord);
        cout << FOOD;
    }


};



int main(){
    initScreen();
    return 0;
}
