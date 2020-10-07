# Vortex

Main features:
  1. Asset Management System
    - has user specify the file path and then paste assets inside of that file
    - user can access these files by using their name without prefix or suffix
  2. State Management System
    - user adds state definitions to states.h as well as creating custom states using vtx::State as the base class
  3. Entity and Component Systems
    - User can define custom entities using vtx::Entity as base class
    - allows user to add components to the entity
    - all managed through an entity manager class
    
# Vortex Game Engine
Custom 2d Game engine using box2d for physics and sfml for graphics

Features
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
