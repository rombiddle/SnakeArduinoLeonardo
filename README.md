# Snake
Snake for Arduino Leonardo

## Requirements:
You will need the following items to implement this project:
- Arduino Leonardo
- 8x8 LED Matrix (dg-d03883 no)
- 2 Push Buttons
- 1 Buzzer
- 8 resistors of 220Ω and 2 resistors of 

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

The 2 push buttons are plugged in PIN A4 and PIN A5.



## Circuit Diagram

![Snake](https://github.com/rombiddle/SnakeArduinoLeonardo/blob/master/29830725_10208761236147876_843359766_o.png?raw=true "Snake")

## Video

[![Serpentuino]()](https://www.youtube.com/watch?v=Qi7nh-p-SI8 "Serpentuino")

## Library

Tone

# License

Arduino Leonardo Snake by Romain BRUNIE, David FOURNIER, Tayeb SEDRAIA.
MIT License.