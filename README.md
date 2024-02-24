# Math-Expression-Solver-with-Graph
## Program in C which parse an expression with one argument x and draw its graph in terminal

Tokenizer parse the expression and create a tree of operations using shunting-yard algorithm.

Graph is drawn using ASCII characters. In range 0..4 * Pi on the x-axis and -1..1 on the y-axis. 
The graph is scaled to 25x80 terminal size. X-axis is on the 13th row and y-axis is reversed upside down.


List of operations:

- `+` = +
- `-` = - binary
- `~` = - unary  
- `*` = *
- `/` = /
- `(` = (
- `)` = )
- `s` = sin(x)  
- `c` = cos(x)
- `t` = tan(x)
- `g` = ctg(x)
- `q` = sqrt(x)
- `l` = ln(x)
- `v` = if value is stored

