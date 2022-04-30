# Ray Tracing on the CPU

### Starting implementation of a CPU based Ray Tracer.

This C++ project implements the Möller–Trumbore ray-triangle intersection algorithm. A bounding volume hierachey acelleration structure is built using surface area huristics. This spacial acelleration structure speeds up the rendering by sorting and splitting the triangles in into leaf nodes using their axis aligned bounding box(AABB). A tree is constructed by dividing the space along the greatest axis and calulating the surface area of the conbined AABB's of the triangles.

#### The Stanford bunny 69,451 triangles - 1920 x 1080 image rendered in 1.29 seconds
![stanford bunny](https://github.com/StrayDev/Ray-Tracing-on-the-CPU/blob/main/Screenshots/image.png)
