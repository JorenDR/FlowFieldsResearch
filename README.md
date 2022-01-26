# FlowFieldsResearch
This project is a research into Flow Fields, how they are built and how they are used.
The project uses the framework we used in the first year of Game Development at DAE.

A Flow Field is a kind of pathfinding algorithm where individual agents don't find their own path. The pathfinding is generally towards a single point, whereto a path is calculated from all locations on the map. This way a single agent just has to look up the path of its underlying point and follow that.

To accomplish this, I used the Dijkstra pathfinding algorithm and ran that for every square in the grid, towards a point assigned by the user.
Then this path is stored for each square, which the agents can easily look up when moving.

At startup, you are greeted with a blank screen.
- **Left-clicking** anywhere will build a flow field towards that point.
- **Right-clicking** will spawn a group of agents who move towards the given point.
- **Space** clears all agents from the program.
