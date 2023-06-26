# physics-engine
Month-long challenge to create a physics engine capable of making a simple platformer.

# Projected Roadmap
Notes on my inital ideas for the challenge.

## Must do:
- [x] Incorportate graphics framework (likely SDL) for rendering rectangles in a window
- [x] Update loop with simple user input
- [ ] AABB rectangle collision
  - [ ] Add visualization for collision states
- [ ] Game object messaging system to handle collision events
- [ ] Add velocity and acceleration systems
- [ ] Add instantaneous forces (for jumping or dashing)
- [ ] Create platforming character controller

## Should do:
- [ ] Create a tilemap system for loading levels
- [ ] Add trigger colliders
  - [ ] Add trigger events to messaging system
- [ ] Partition colliders into KD-Tree to reduce collision checks ( O(n^2) -> O(nlogn) )
- [ ] Add raycasting
  - [ ] Add visualization

## Could do:
- [ ] Run physics update loop on separate thread
  - [ ] Hard code physics update rate independant of framerate
- [ ] Implement collision layers
- [ ] Build out multiple platforming levels

## Won't do:
- [ ] Game UI
- [ ] Classic platformer features:
  - [ ] Enemy AI
  - [ ] Life system
  - [ ] ...
