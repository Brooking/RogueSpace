# Rogue Space (structure) 
## ___to do list___
### Bugs
  - [x] Surface vscode debugger not working
  - [x] run in normal terminal (local config)
  - [ ] smart pointers for all world objects
  - [ ] Rectify hero being known to the floor(?)
### Input
#### Keyboard
  - [x] add diagonal input
#### Mouse
  - [ ] show mouse cursor
  - [ ] implement hover info
  - [ ] implement click to move
### Output
#### Curses
  - [x] static values on RealCurses
  - [x] object oriented interface for curses
  - [x] move curses wrapper to its own library
### Text Screen
  - [x] auto-center the hero (with tests)
  - [x] directional walls (with tests)
### Windows
  - [ ] implement panes
  - [ ] implement status pane for hero
  - [ ] implement hover pane
  - [ ] implement map on tab
  - [ ] implement inventory
  - [ ] implement health
### Features
#### Monster
  - [x] add a monster to move around
  - [ ] limit monster's reaction to hero/dog in field of view
  - [ ] give monster stateful AI : wandering/seeking, beeline, beeline-to-last-seen, wandering back, etc
#### Lighting
  - [x] Add visibility to hero
  - [x] Persist seen walls
  - [ ] differentiate between "in FOV+lit" and "in FOV+in sight"
  - [ ] may need to store range with FOV entries

