# Vortex Game Engine
Custom 2d Game engine using box2d for physics and sfml for graphics

# Features
Advanced Entity Component System
  - Manages entities, components and systems independently. Very low load on cpu compared to object oriented based approach
  
Basic Asset Managment System
  - can be easily modified to hold any number of different type of assets through modification of the AssetHolder.h header file

State Management System
  - Handles the logic and rendering of all states, and switches between them

Input Management System
  - Handles user input such as keyboard and mouse
  
Default physics and rendering systems
  - Uses box2d to handle physics sfml for rendering
  - Automatically handled using physics and render systems (see the Rise or Sandbox folders for examples on usage)
