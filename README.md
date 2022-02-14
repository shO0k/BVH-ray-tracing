# BVH-ray-tracing GL;HF

A Bounding Volume Hierarchy (BVH) is a data structure containing nested geometric objects wrapped in bounding volumes.

Example of a BVH: https://image1.slideserve.com/3410272/bounding-volume-hierarchies-l.jpg

More Information on BVH's: https://en.wikipedia.org/wiki/Bounding_volume_hierarchy

Given a map of boxes, count how many a given ray intersects a box within the map.
  - ray consists of a point of origin and a direction
  - boxes can contain other boxes

Ray format: 
  - 0 0 1 1 represents a ray with a point of origin (0.00,0.00), Slope: 1, Direction: forwards.

Box format: 
  - 0 0 0 10 10 1 2 3 represents a "parent" box with the bottom left point (0.00,0.00), top right point (10.00, 10.00) and "children" on lines 1, 2, 3.

Examples:
  - ray: 0 0 1 1 intersects a box: 2 2 3 3
  - ray: -1 -1 1 0 does NOT intersect a box: 2 2 3 3

In addition to counting the number of intersections on each box, we must also:
  - check the map for correctness (no solid box overlap or "children" not fully contained by their "parents")
  - convert a non-numerical value inputted for slope to a vertical slope
