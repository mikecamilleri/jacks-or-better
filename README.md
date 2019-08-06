# Jacks or Better

This is a _Jacks or Better_ video poker game impletmented in C99 with an `ncurses` user inerface. I wrote this game over a few days primarily to refresh my C language skills. This is a fully playable game, but there are aspects that could be improved. They are noted below or in the source code. For the rules, see [Wikipedia](https://en.wikipedia.org/wiki/Video_poker).

```
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
$  ROYAL FLUSH ...... | 250 | 500 | 750 | 1000 | *4000 |                       $
$  STRAIGHT FLUSH ... |  50 | 100 | 150 |  200 |   250 |                       $
$  4 OF A KIND ...... |  25 |  50 |  75 |  100 |   125 |   J a c k s           $
$  FULL HOUSE ....... |   9 |  18 |  27 |   36 |    45 |       - o r -         $
$  FLUSH ............ |   6 |  12 |  18 |   24 |    30 |         B e t t e r   $
$  STRAIGHT ......... |   4 |   8 |  12 |   16 |    20 |                       $
$  3 OF A KIND ...... |   3 |   6 |   9 |   12 |    15 |                       $
$  TWO PAIR ......... |   2 |   4 |   6 |    8 |    10 |   / \   o   ^ ^  / \  $
$  JACKS OR BETTER .. |   1 |   2 |   3 |    4 |     5 |   \ /  o|o   v   -|-  $
$                                                                              $
$                        TWO PAIR                                              $
$  +-------+  +-------+  +-------+  +-------+  +-------+                       $
$  | 8     |  | 8     |  | K     |  | 7     |  | 7     |   DEAL/DRAW  [ENTER]  $
$  | ♦     |  | ♣     |  | ♦     |  | ♥     |  | ♦     |   HOLD         [1-5]  $
$  |   / \ |  |    o  |  |   / \ |  |   ^ ^ |  |   / \ |   BET          [+/-]  $
$  |   \ / |  |   o|o |  |   \ / |  |    v  |  |   \ / |   EXIT           [X]  $
$  +-------+  +-------+  +-------+  +-------+  +-------+                       $
$   HELD [1]   HELD [2]        [3]   HELD [4]   HELD [5]                       $
$                                                                              $
$  PAID 10                 BET 5          CREDIT     975                       $
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
```

## Building

This program has only been tested on MacOS but should compile on any Unix-like operating sytem. A simple build script, `build.sh` has been provided.

## Known Issues and Areas of Improvement

- The handling of window resizing needs to be improved.
- Color would make the cards more readable. 
- Should be tested on other operating systems.
- Should have tests.

## License

See the `LICENSE` file.

```
    Jacks or Better
    Copyright (C) 2019 Michael Camilleri <mike@mikecamilleri.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
