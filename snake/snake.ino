/*
 * Author: Romain BRUNIE, David FOURNIER, Tayeb SEDRAIA
 * Purpose: Play the snake game using matrix 8X8.
 * Language:  C
 */

/**
 * This library is used to play a melody. 
 * https://www.arduino.cc/en/Tutorial/toneMelody
 *
 */
#include "pitches.h"

/* These constants is called for LED matrix 8x8 on the pixel at row */
#define PIN_ROW1 2
#define PIN_ROW2 3
#define PIN_ROW3 4
#define PIN_ROW4 5
#define PIN_ROW5 A3
#define PIN_ROW6 A2
#define PIN_ROW7 A1 
#define PIN_ROW8 A0 

/* These constants is called for LED matrix 8x8 on the pixel at column */
#define PIN_COL1 6
#define PIN_COL2 7
#define PIN_COL3 8
#define PIN_COL4 9
#define PIN_COL5 10
#define PIN_COL6 11
#define PIN_COL7 12
#define PIN_COL8 13 

#define PIN_INPUT_LEFT A4 /* This constant is called for the left button yellow */
#define PIN_INPUT_RIGHT A5 /* This constant is called for the right black button */
#define PIN_INPUT_PLAY_PAUSE 1 /* This constant is called for the play/pause red button */

#define MAX_BODY_LENGTH 13 /* This constant is called to give a max size to the snake */
#define GAME_AREA_WIDTH 8 /* This constant is called to give the width of our game area. */
#define GAME_AREA_HEIGHT 8 /* This constant is called to give the height of our game area. */
#define GAME_OVER_TIME 3000 

#define DIRECTION_DOWN 0 /* This constant is called to go down */
#define DIRECTION_LEFT 1 /* This constant is called to go left */
#define DIRECTION_UP 2 /* This constant is called to go up */
#define DIRECTION_RIGHT 3 /* This constant is called to go right */

typedef struct p
{
    int x;
    int y;
} Position;

Position body[MAX_BODY_LENGTH];
int lastInput;
int pauseInput;
int head;
int tail;
int bodyLength;
int direction;
Position food;
int gameover;
int score;
int elapsedTime;
bool readInput;
unsigned long previousTime;
bool musicWinPlayed;
int timeDifficult;
bool isPaused;
int melody[] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
int melodyEat[] = { NOTE_C4, NOTE_G3, NOTE_C4, NOTE_G3,NOTE_C4, NOTE_G3,NOTE_C4, NOTE_G3,NOTE_C4, NOTE_G3,NOTE_C4, NOTE_G3,NOTE_C4, NOTE_G3,NOTE_C4, NOTE_G3 };
int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4 };
int eatingTone = NOTE_C4;

/**
 * Turn the LED matrix 8x8 on the pixel at row and column. This function is called several times.
 * 
 * @param row Position to be lit on the row 
 * @param column Position to be lit on the column
 */
void setPixel(int row, int column)
{
    digitalWrite(PIN_ROW1, LOW);
    digitalWrite(PIN_ROW2, LOW);
    digitalWrite(PIN_ROW3, LOW);
    digitalWrite(PIN_ROW4, LOW);
    digitalWrite(PIN_ROW5, LOW);
    digitalWrite(PIN_ROW6, LOW);
    digitalWrite(PIN_ROW7, LOW);
    digitalWrite(PIN_ROW8, LOW);
    digitalWrite(PIN_COL1, HIGH);
    digitalWrite(PIN_COL2, HIGH);
    digitalWrite(PIN_COL3, HIGH);
    digitalWrite(PIN_COL4, HIGH);
    digitalWrite(PIN_COL5, HIGH);
    digitalWrite(PIN_COL6, HIGH);
    digitalWrite(PIN_COL7, HIGH);
    digitalWrite(PIN_COL8, HIGH);
        
    switch(column)
    {
        case 0: digitalWrite(PIN_COL1, LOW); break;
        case 1: digitalWrite(PIN_COL2, LOW); break;
        case 2: digitalWrite(PIN_COL3, LOW); break;
        case 3: digitalWrite(PIN_COL4, LOW); break;
        case 4: digitalWrite(PIN_COL5, LOW); break;
        case 5: digitalWrite(PIN_COL6, LOW); break;
        case 6: digitalWrite(PIN_COL7, LOW); break;
        case 7: digitalWrite(PIN_COL8, LOW); break;
        default: break;
    }

    switch(row)
    {
        case 0: digitalWrite(PIN_ROW1, HIGH); break;
        case 1: digitalWrite(PIN_ROW2, HIGH); break;
        case 2: digitalWrite(PIN_ROW3, HIGH); break;
        case 3: digitalWrite(PIN_ROW4, HIGH); break;
        case 4: digitalWrite(PIN_ROW5, HIGH); break;
        case 5: digitalWrite(PIN_ROW6, HIGH); break;
        case 6: digitalWrite(PIN_ROW7, HIGH); break;
        case 7: digitalWrite(PIN_ROW8, HIGH); break;
        default: break;
    }
}

/**
 * Check if the food position is valid.
 * \returns     The boolean result of the algorithm 
 */
bool foodPositionIsValid()
{
    if (food.x < 0 || food.y < 0) return false;

    for (int i = tail; i <= (head > tail ? head : MAX_BODY_LENGTH - 1); i++)
    {
        if (body[i].x == food.x && body[i].y == food.y) return false;
    }

    if (head < tail)
    {
        for (int i = 0; i <= head; i++)
        {
            if (body[i].x == food.x && body[i].y == food.y) return false;
        }
    }
    return true;
}


/**
 * Check if the game is lost. This function is called several times on the loop.
 * 
 */
void checkGameover()
{
    for (int i = tail; i <= (head > tail ? head - 1 : MAX_BODY_LENGTH - 1); i++)
    {
        if (body[head].x == body[i].x && body[head].y == body[i].y)
        {
            gameover = GAME_OVER_TIME;
            return;
        }
    }

    if (head < tail)
    {
        for (int i = 0; i < head; i++)
        {
            if (body[head].x == body[i].x && body[head].y == body[i].y)
            {
                gameover = GAME_OVER_TIME;
                return;
            }
        }
    }
}


/**
 * This function change randomly position of the food on game area if the position food is not valid
 * 
 */
void spawnFood()
{
    while (!foodPositionIsValid())
    {
        food = 
        {
            random(GAME_AREA_WIDTH), 
            random(GAME_AREA_HEIGHT) 
        };

        Serial.print("food spawn");
    }
    Serial.print("food spawn invalid");
}


/**
 * This function turns on the LEDs to draw the snake and the position of the food. This function is called several times on the loop.
 * 
 */
void draw()
{
    for (int i = tail; i <= (head > tail ? head : MAX_BODY_LENGTH - 1); i++)
    {
        setPixel(body[i].x, body[i].y);
    }

    if (head < tail)
    {
        for (int i = 0; i <= head; i++)
        {
            setPixel(body[i].x, body[i].y);
        }
    }
    setPixel(food.x, food.y);
}


/**
 * This function allows you to change the direction according to the selected postition
 * We have 4 direction : DIRECTION_LEFT, DIRECTION_RIGHT, DIRECTION_UP, DIRECTION_DOWN
 * 
 */
void move()
{
    tail = tail + 1 == MAX_BODY_LENGTH ? 0 : tail + 1;
    Position prevHead = body[head];
    head = head + 1 == MAX_BODY_LENGTH ? 0 : head + 1;
    body[head] = 
    { 
        prevHead.x + (direction == DIRECTION_LEFT ? -1 : (direction == DIRECTION_RIGHT ? 1 : 0)), 
        prevHead.y + (direction == DIRECTION_UP ? -1 : (direction == DIRECTION_DOWN ? 1 : 0)) 
    };
    body[head].x = body[head].x < 0 ? GAME_AREA_WIDTH - 1 : (body[head].x >= GAME_AREA_WIDTH ? 0 : body[head].x);
    body[head].y = body[head].y < 0 ? GAME_AREA_HEIGHT - 1 : (body[head].y >= GAME_AREA_HEIGHT ? 0 : body[head].y);
}

/**
 * Displays the score on the data matrix. The numbers range from 0 to 10. By default we display 12 to the user
 * 
 * @param score  Result of the number of eating food
 */
void printScore(int score)
{
    switch(score)
    {
        case 0:
            setPixel(5,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            setPixel(5,4);
            setPixel(4,3);
            setPixel(5,5);
            setPixel(4,5);
            setPixel(3,5);
            setPixel(2,5);
            setPixel(1,5);
            setPixel(1,4);
            break;
        case 1: 
            setPixel(5,4);
            setPixel(4,4);
            setPixel(3,4);
            setPixel(2,4);
            setPixel(1,4);
            break;
        case 2: 
            setPixel(5,5);
            setPixel(3,5);
            setPixel(3,4);
            setPixel(5,3);
            setPixel(4,3);
            setPixel(3,3);
            setPixel(1,3);
            setPixel(5,4);
            setPixel(1,4);
            setPixel(1,5);
            setPixel(2,5);
            break;
        case 3: 
            setPixel(5,5);
            setPixel(3,5);
            setPixel(3,4);
            setPixel(5,3);
            setPixel(4,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            setPixel(5,4);
            setPixel(1,4);
            setPixel(1,5);
            break;
        case 4: 
            setPixel(5,5);
            setPixel(4,5);
            setPixel(3,5);
            setPixel(3,4);
            setPixel(5,3);
            setPixel(4,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            break;
        case 5: 
            setPixel(5,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            setPixel(5,4);
            setPixel(3,4);
            setPixel(5,5);
            setPixel(4,5);
            setPixel(3,5);
            setPixel(1,5);
            setPixel(1,4);
            break;
        case 6: 
            setPixel(5,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            setPixel(5,4);
            setPixel(3,4);
            setPixel(5,5);
            setPixel(4,5);
            setPixel(3,5);
            setPixel(2,5);
            setPixel(1,5);
            setPixel(1,4);
            break;
        case 7: 
            setPixel(5,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            setPixel(5,4);
            setPixel(4,3);
            setPixel(5,5);
            break;
        case 8: 
            setPixel(5,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            setPixel(5,4);
            setPixel(4,3);
            setPixel(5,5);
            setPixel(4,5);
            setPixel(3,5);
            setPixel(2,5);
            setPixel(1,5);
            setPixel(1,4);
            setPixel(3,4);
            break;
        case 9: 
            setPixel(5,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            setPixel(5,4);
            setPixel(4,3);
            setPixel(5,5);
            setPixel(4,5);
            setPixel(3,5);
            setPixel(1,5);
            setPixel(1,4);
            setPixel(3,4);
            break;
        case 10: 
            setPixel(5,5);
            setPixel(4,5);
            setPixel(3,5);
            setPixel(2,5);
            setPixel(1,5);
            setPixel(5,1);
            setPixel(3,1);
            setPixel(2,1);
            setPixel(1,1);
            setPixel(5,2);
            setPixel(4,1);
            setPixel(5,3);
            setPixel(4,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            setPixel(1,2);
            break;
        case 999: 
            // restart icon
            setPixel(1,6);
            setPixel(1,5);
            setPixel(2,6);
            setPixel(2,2);
            setPixel(3,6);
            setPixel(3,3);
            setPixel(3,2);
            setPixel(3,1);
            setPixel(4,6);
            setPixel(4,4);
            setPixel(4,3);
            setPixel(4,2);
            setPixel(4,1);
            setPixel(5,6);
            setPixel(5,2);
            setPixel(4,0);
            setPixel(6,6);
            setPixel(6,5);
            setPixel(6,4);
            setPixel(6,3);
            setPixel(6,2);
            break;
        default: 
            // score 10
            setPixel(5,5);
            setPixel(4,5);
            setPixel(3,5);
            setPixel(2,5);
            setPixel(1,5);
            setPixel(5,1);
            setPixel(3,1);
            setPixel(2,1);
            setPixel(1,1);
            setPixel(5,2);
            setPixel(4,1);
            setPixel(5,3);
            setPixel(4,3);
            setPixel(3,3);
            setPixel(2,3);
            setPixel(1,3);
            setPixel(1,2);
            break;
    }
}

/**
 * Check if the food has been eaten. This function is used when the food has been eaten. 
 * We increment the score each time and increase the speed snake.
 */
void eat()
{
    // Check if head is at food position
    if (body[head].x == food.x && body[head].y == food.y)
    {
        // We increase the difficulty each time the snake eats 50 ms
        if (timeDifficult > 100)
        {
            timeDifficult -= 75;
        }
        // Play randomly a sound
        tone(0, melodyEat[score], 1000/8);

        if (bodyLength < MAX_BODY_LENGTH)
        {
            bodyLength++;
            tail--;
            if (tail < 0) tail = MAX_BODY_LENGTH - 1;
        }
        score++;
        food = { -1, -1 };
        spawnFood();
    }
}


/**
 * Initializing our variables for snake size. The size of the snake: 3. Position of the food on the matrix. Snake speed : 500. Direction of the snake : DOWN
 * This function is called at the beginning of the game and at the end of the game
 */
void reset()
{
    body[0] = { 3,3 };
    body[1] = { 3,4 };
    body[2] = { 3,5 };
    isPaused = false;
    bodyLength = 3;
    head = 2;
    tail = 0;
    direction = DIRECTION_DOWN;
    food = {6, 7};
    gameover = 0;
    elapsedTime = 0;
    score = 0;
    spawnFood();
    readInput = true;
    musicWinPlayed = false;
    timeDifficult = 700;
}

/**
 * Play a Melody using the tone() function and stop a Melody using noTone() function
 * This function is called once the finished part
 */
void musicWin()
{
    musicWinPlayed = true;
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {
        // to calculate the note duration, take one second divided by the note type.
        int noteDuration = 1000 / noteDurations[thisNote];
        tone(0, melody[thisNote], noteDuration);
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);

        // stop the tone playing
        noTone(0);
    } 
}

/**
 * Define the pinMode : Matrix and buttons.
 * Initialise the variable with the function reset
 */
void setup()
{   
    pinMode(PIN_ROW1, OUTPUT);
    pinMode(PIN_ROW2, OUTPUT);
    pinMode(PIN_ROW3, OUTPUT);
    pinMode(PIN_ROW4, OUTPUT);
    pinMode(PIN_ROW5, OUTPUT);
    pinMode(PIN_ROW6, OUTPUT);
    pinMode(PIN_ROW7, OUTPUT);
    pinMode(PIN_ROW8, OUTPUT);
    pinMode(PIN_COL1, OUTPUT);
    pinMode(PIN_COL2, OUTPUT);
    pinMode(PIN_COL3, OUTPUT);
    pinMode(PIN_COL4, OUTPUT);
    pinMode(PIN_COL5, OUTPUT);
    pinMode(PIN_COL6, OUTPUT);
    pinMode(PIN_COL7, OUTPUT);
    pinMode(PIN_COL8, OUTPUT);

    pinMode(PIN_INPUT_LEFT, INPUT);
    pinMode(PIN_INPUT_RIGHT, INPUT);
    pinMode(PIN_INPUT_PLAY_PAUSE, INPUT_PULLUP);

    reset(); 
}

/**
 * This function is used when a block of code needs to be executed several number of times.
 * digitalRead of button pause (digital) return 0 on click
 * digitalRead of button right/left (analog) return 1 on click
 */
void loop()
{   
    unsigned long currentTime = millis(); 

    if(!gameover)
    {
        draw();
        elapsedTime += currentTime - previousTime;
        Serial.print("digit read : ");
        Serial.print(!digitalRead(PIN_INPUT_PLAY_PAUSE));
        Serial.print(" ");
        Serial.println(pauseInput);
        Serial.print("isPaused1 = ");
        Serial.println(isPaused); 
        int reading = !digitalRead(PIN_INPUT_PLAY_PAUSE);

        if(reading && pauseInput) 
        {
            Serial.print("start pause/play button ");
            Serial.print(reading);
            Serial.print(" ");
            Serial.println(pauseInput);
            if (isPaused)
            {
                Serial.println("play");
            }
            else
            {
                Serial.print("pause");
                delay(9999999999);
            }
            isPaused = !isPaused;
            Serial.println("end pause/play button");
        }
        Serial.print("isPaused1 = ");
        Serial.println(isPaused);
        // avoid to play/pause when the pause button to stay pressed 
        pauseInput = digitalRead(PIN_INPUT_PLAY_PAUSE);

        if (!isPaused)
        {
            if(elapsedTime > timeDifficult)
            {
                move();
                eat();
                checkGameover();
                elapsedTime = 0;
                readInput = true;
            }
            if(readInput)
            {
                if(digitalRead(PIN_INPUT_LEFT) && !lastInput)
                {
                    Serial.println("left");
                    direction = (direction + 1) % 4;
                    readInput = false; 
                }
                if(digitalRead(PIN_INPUT_RIGHT) && !lastInput)
                { 
                    Serial.println("right");
                    direction = (4 + direction-1) % 4; 
                    readInput = false; 
                }
            }
            // avoid to turn when the button right/left to stay pressed 
            lastInput = digitalRead(PIN_INPUT_RIGHT) || digitalRead(PIN_INPUT_LEFT);
        }
        
    }
    else
    {
        if (!musicWinPlayed)
        {
            musicWin();
        }
        unsigned long starttime = millis();
        unsigned long endtime = starttime;
        while ((endtime - starttime) <=4000)
        {
            printScore(score);
            endtime = millis();
        }
        restart();
    }
    previousTime = currentTime;
}

/**
 * This function is used to restart the game once it is finished.
 * Displays an arrow. Press one of the buttons to start a new game
 */
void restart()
{
    bool restartButton = true;
    while (restartButton)
    {
        printScore(999);
        if(digitalRead(PIN_INPUT_RIGHT) || digitalRead(PIN_INPUT_LEFT) || digitalRead(PIN_INPUT_PLAY_PAUSE))
        {
            restartButton = false;
        }
    }
    reset();
}