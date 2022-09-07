
(EN)  Cellular automata: Game of life 

They are the maximum simplification of autonomous agents. They evolve over time based on their current status and the state of their closest neighbors. It was discovered by Stanislaw Ulam and John von Neumann and, later, studied by Wolfram.
Cellular automata are applied in many fields such as Chemistry, Biology, Physics, Art and generative music.

In this case, I have reproduced John Horton Conway's Game of Life, which implements a 2D cellular automata with 3 very simple rules:
- A cell with less than two neighbors dies of loneliness
- A cell with more than three neighbors dies of overpopulation
- If a dead cell has three neighbors, it becomes alive by reproduction.

I have added controls to alter the above limits.

----------------------------------------------------------------------
(ES)Autómatas celulares: Juego de la vida

Son la simplificación máxima de los agentes autonómos. Evolucionan en el tiempo en base a su estado actual y el de sus vecinos más próximos. Fue descubierto por  Stanislaw Ulam and John von Neumann y , posteriormente, estudiado por Wolfram.
Los automatas celulares se aplican en muchos ámbitos como la Química, Biología, Física, Arte y música generativa.

En este caso, he reproducido el Juego de la Vida de John Horton Conway, que implementa un automata celular en 2D con 3 reglas muy simples:
- Una célula con menos de dos vecinos muere de soledad
- Una célula con más de tres vecinos muere de sobrepoblación
- Si célula muerta tiene tres vecinos pasa a estar viva por reproducción.

He añadido controles para alterar los límites anteriores.




Source  code and assets in: 
(https://github.com/juandrh/SystemOfObjects/tree/main/System04/

Main sources:
Elementary Cellular Automaton - Wolfram MathWorld (https://mathworld.wolfram.com/ElementaryCellularAutomaton.html)
The Nature of Code by DANIEL SHIFFMAN: https://natureofcode.com/
Unreal Engine Documentation: https://docs.unrealengine.com/5.0/en-US/
Unreal Engine 5 C++ Developer: Learn C++ & Make Video Games: https://www.udemy.com/share/101XRs3@OpnCZpq_K9nP6l2C8_L-D3NHVtfTzftwqXk8b64iszJUWY8dWxl7Scmdj8mb-Cf5/
