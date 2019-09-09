# Rogue Space (structure) 
## ___to do list___
### Bugs
  - [x] Surface vscode debugger not working
  - [ ] run in normal terminal (local config)
  - [x] not showing @ on start
  - [x] blank spot follows @
  - [x] in-sight circle lags behind hero
  - [x] coalesce mini+main
  - [x] consistent virtual/override usage
  - [x] select char appears in terminal after execution stops
  - [x] unseen actors obscure seen floors
### Structure
  - [ ] Rectify hero being known to the floor(?)
  - [x] smart pointers for all world objects
    - [x] shared_from_this
      - [x] Hero
      - [x] Floor
    - [x] ~Screen not getting called
    - [x] things should not self place
  - [ ] Move everything up one directory
  - [x] Create a common library
  - [x] enhance token system
    - [x] move wall shape to world
    - [x] break none/seen/visible/lit out of token
  - [x] move visibility tools underneath world
  - [x] move io underneath ui
  - [x] create game class
  - [x] implement iActor
  - [x] change the executable name to roguespace.out
### Input
#### Keyboard
  - [x] add diagonal input
#### Mouse
  - [ ] show mouse cursor
  - [ ] implement hover info
  - [ ] implement click to move
#### Time Management
  - [x] implement time-tic based speed differentiation
    - [x] timeline
    - [ ] time-per-action, (speed setting?)
    - [x] iActor
    - [ ] different timer for UI effects
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
  - [ ] rat passes hero to get to old 'target'
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
  - [ ] dog should pathfind (and always know where hero is)
  - [ ] dog always visible
  - [ ] monster::move should have central implementation
#### Lighting
  - [x] Add visibility to hero
  - [x] Persist seen walls
  - [x] add lights
  - [x] lights color structures yellow
  - [x] differentiate between "in FOV+lit" and "in FOV+in sight"
  - [x] may need to store range with FOV entries
  - [ ] add directional lighting perception
  - [ ] implement lit directionality
  - [ ] implement hiding walls behind walls
#### Hero
  - [x] Add sight distance
  - [ ] add push-past
  - [ ] create iHero for use in game.cpp
  - [x] add stamina
    - [x] add 'run' (mode: 'r')
      - [x] double speed (faster than monsters, where walking is slower)
      - [x] uses stamina
    - [x] add stamina to status window
    - [x] recover stamina on walk and rest
#### Visibility
  - [x] Line of sight
  - [x] Field of view
  - [x] Dijkstra map
  - [x] Pathing
  - [x] Change api semantics to hero.can_see()
  - [x] Make lighted tiles visible only if in los
  - [x] 'Seen' tiles determined by asking for token
  - [ ] add always-visible monsters for debugging