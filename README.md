# Game-lightning-conversion

## About
The aim of this game is to identify a binary number presented with 5 LED´s, within a time interval. To prepare this project, I used an arduino uno, a board, 5 LED´s, a button and other necessary components. The following image shows the circuit diagram:

![Circuit Diagram](res/Diagrama%20do%20circuito%20(TinkerCad).png "Circuit Diagram")

## Game
The game consists of the following steps:

- A random number is generated, converted into binary and displayed on the 5 LED´s;
- The player must press a button successively, increasing a decimal counter until its value matches the binary displayed. This counter returns to zero whenever the maximum limit is reached;
- The player has a time limit to select the decimal number that corresponds to the binary conversion shown. At the end of the time, the game will inform you whether the number is correct or not, restarting with a new random number;
- If the number is correct, the game prints an informative message, turning the LED´s on and off sequentially.

If the button is pressed for one second, the game restarts.

## License
Distributed under the MIT License. See [LICENSE](LICENSE) for more information.