# Rogue Space (structure) 
## ___to do list___
### Bugs
  - [x] Surface vscode debugger not working
  - [ ] run in normal terminal (local config)
  - [x] not showing @ on start
  - [x] blank spot follows @
  - [x] in-sight circle lags behind hero
  - [x] smart pointers for all world objects
    - [x] shared_from_this
      - [x] Hero
      - [x] Floor
    - [ ] ~Screen not getting called
    - [x] things should not self place
  - [ ] Rectify hero being known to the floor(?)
  - [ ] Move everything up one directory
  - [ ] coalesce mini+main
  - [x] consistent virtual/override usage
### Input
#### Keyboard
  - [x] add diagonal input
#### Mouse
  - [ ] show mouse cursor
  - [ ] implement hover info
  - [ ] implement click to move
#### Time Management
  - [ ] implement time-tic based speed differentiation
### Output
#### Curses
  - [x] static values on RealCurses
  - [x] object oriented interface for curses
  - [x] move curses wrapper to its own library
  - [ ] solve ncurses on wsl bash
### Text Screen
  - [x] auto-center the hero (with tests)
  - [x] directional walls (with tests)
  - [ ] add horizontal spacing to square things up
  - [x] implement colors
  - [x] show white visible stuff & grey 'seen' stuff
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
  - [x] limit monster's reaction to hero in field of view
  - [x] limit monster's range to view hero
  - [ ] add monster reaction to dog
  - [ ] add monster 'bounce' off of hero
  - [ ] add monster smelling
  - [ ] add monster hearing
  - [ ] give monster stateful AI : wandering/seeking, beeline, beeline-to-last-seen, wandering back, etc
  - [x] add pathfinding
    - [x] separate dijkstra
    - [ ] pathing
    - [ ] tests
  - [x] add bee and rat
#### Lighting
  - [x] Add visibility to hero
  - [x] Persist seen walls
  - [x] add lights
  - [x] lights color structures yellow
  - [x] differentiate between "in FOV+lit" and "in FOV+in sight"
  - [x] may need to store range with FOV entries
#### Hero
  - [x] Add sight distance
#### Visibility
  - [x] Line of sight
  - [x] Field of view
  - [x] Dijkstra map
  - [x] Pathing
  - [x] Change api semantics to hero.can_see()
  - [x] Make lighted tiles visible only if in los
  - [x] 'Seen' tiles determined by asking for token