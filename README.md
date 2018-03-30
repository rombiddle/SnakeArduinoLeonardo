# Snake
Snake game for Arduino Leonardo

## Requirements:
You will need the following items to implement this project:
- Arduino Leonardo
- 8x8 LED Matrix (dg-d03883 no)
- 2 Push Buttons
- 1 Buzzer
- 8 resistors of 220Ω for the matrix and 2 resistors of 10kΩ for the push buttons

## Rules

- Don't run the snake into his own tail if you want to stay alive.
- Use the 2 push buttons to turn right or left.
- Eat the dots to gain points.
- More point you get, faster the snake is

## 8x8 LED Matrix (dg-d03883 no)

|    |    |    |    |    |    |    |    | **A0** |
|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|
|    |    |    |    |    |    |    |    | **A1** |
|    |    |    |    |    |    |    |    | **A2** |
|    |    |    |    |    |    |    |    | **A3** |
|    |    |    |    |    |    |    |    | **5** |
|    |    |    |    |    |    |    |    | **4** |
|    |    |    |    |    |    |    |  X  | **3** |
|    |    |    |    |    |    |    |    | **2** |
| **13** | **12** | **11** | **10** | **9**  | **8**  | **7**  | **6**  | **PIN** |

In order to turn on the led with the "X", you have to set up PIN 3 to HIGH and set up PIN 6 to LOW.

## Push Buttons

The 2 push buttons are plugged in on PIN A4 and on PIN A5.

## Buzzer

The buzzer is plugged in on PIN 0.

## Circuit Diagram

![Snake](https://github.com/rombiddle/SnakeArduinoLeonardo/blob/master/images/29830725_10208761236147876_843359766_o.png?raw=true "Snake")

## Video

[![Snake](https://github.com/rombiddle/SnakeArduinoLeonardo/blob/master/images/29883488_10208761250068224_692720117_o.png?raw=true)](https://www.youtube.com/watch?v=Qi7nh-p-SI8 "Snake")

## Library

Tone

## Extra feature (Play/Pause button)

We tried to add a push button to Play/Pause the game on PIN 1.

Our first problem was that the push button controlling directions are Analog! In this case, the digitalRead return 1 on click. The push button controlling Play/Pause is Digital (cf Arduino PIN 1) and the digitalRead return 0 on click.

Our second problem was that the game pauses by itself whenever the snake eat. We could not fix this problem and went back to the game version without this feature.

# License

Arduino Leonardo Snake by Romain BRUNIE, David FOURNIER, Tayeb SEDRAIA.
MIT License.