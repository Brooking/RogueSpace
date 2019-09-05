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
    - [x] ~Screen not getting called
    - [x] things should not self place
  - [ ] Rectify hero being known to the floor(?)
  - [ ] Move everything up one directory
  - [x] coalesce mini+main
  - [x] consistent virtual/override usage
  - [x] select char appears in terminal after execution stops
  - [ ] both sides of walls are illuminated (translucent)
  - [ ] enhance token system
    - [ ] move wall shape to world
    - [ ] implement lit directionality
    - [ ] break none/seen/visible/lit out of token
  - [x] move visibility tools underneath world
  - [x] move io underneath ui

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
  - [x] implement mosaic (container)
  - [x] implement panes
    - [x] make iPane
    - [x] finish iUpdate system for pane updates
    - [ ] normalize start+size vs. sides rect representation
    - [ ] make each pane a Rect (or iRect) for convenience
    - [ ] make self sizing panes attached to walls
      - [ ] keep having immutable panes...
  - [x] implement status pane for hero
    - [ ] implement stats for hero
    - [ ] status pane should dictate its own size
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
  - [ ] add directional lighting perception
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