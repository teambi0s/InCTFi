# MIZ

## Challenge Description

Senpai plis find me a way.

### Short write up

Miz is a fairly simple maze challenge written in rust. 

- `miz::bacharu::Kikai::new` - Initializes the maze
- `miz::bacharu::Kikai::run` - Takes care of traversing the maze according to our input

The input can be

- "l"  ⇒ go right
- "k" ⇒ go down
- "h" ⇒ go left
- "j" ⇒ go up

The properties of the maze

- "0" ⇒ Path to traverse
- "1" ⇒ Walls
- "2" ⇒ Final win position

Giving a combination of this input we can traverse the maze.

The start location is at (0, 13)

The end location where "2" is present is at (24, 19)

We can use the python module `mazelib` and solve the maze

### Flag

inctf{mizes_are_fun_or_get}

### Author

Freakston, silverf3lix