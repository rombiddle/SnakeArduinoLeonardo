# Snake
Snake for Arduino Leonardo

## Requirements:
You will need the following items to implement this project:
- Arduino Leonardo
- 8x8 LED Matrix (dg-d03883 no)
- 2 Push Buttons
- 1 Buzzer

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

In order to turn on the led with the "X", you have to set up to HIGH the PIN 3 et set up to LOW the PIN 6

## Circuit Diagram

![Serpentuino](https://github.com/raulbojalil/serpentuino/blob/master/snake.png?raw=true "serpentuino")

## Video

[![Serpentuino](https://github.com/raulbojalil/serpentuino/blob/master/video.png)](https://www.youtube.com/watch?v=j3Xj868APJs "Serpentuino")

## Library

Tone

# License

Arduino Leonardo Snake by Romain BRUNIE, David FOURNIER, Tayeb SEDRAIA.
MIT License.