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
