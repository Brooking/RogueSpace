#RogueSpace Structure
An experiment in detaching world structure from UI represenation

* Overall structure
    * world
        * this is where all of the action takes place, all objects are here
            * terrain
                * floor
                * locations
                    * encoded los & fov
                * walls
            * things
                * items
                * monsters
                * hero
                    * inventory
                    * skills
                    * attributes
    * UI
        * this is what the user sees
            * screen
            * frame
            * panes
        * this is where the user interacts
            * mouse
                * left click
                * right click
                * hover
            * keyboard
    * game
        * this is the engine that drives things forward

* Integral Types
    * unsigned int
        * row/cell
        * sizes
        * indices
        * time
    * (signed) int
        * input keys
        * color character
