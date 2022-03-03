# BVH-ray-tracing GL;HF

A Bounding Volume Hierarchy (BVH) is a data structure containing nested geometric objects wrapped in bounding volumes.

Example of a BVH: https://image1.slideserve.com/3410272/bounding-volume-hierarchies-l.jpg

More Information on BVH's: https://en.wikipedia.org/wiki/Bounding_volume_hierarchy

Given a map of 2-dimensional boxes, count how many times a given ray intersects boxes within the map.
  - a ray consists of a point of origin and a direction
  - boxes can contain other boxes ("parents" contain "children")

Ray format (not dissimmilar to the parametric vector equation of a line): 
  - 0 0 1 1 represents a ray with a point of origin (0.00,0.00), Slope: 1, Direction: forwards.
  - 1 2 -1 0 represents a ray with a point of origin (1.00,2.00), Slope: -1, Direction: backwards.

Box format: 
  - 0 0 0 10 10 1 2 3 represents a "parent" box with the bottom left point (0.00,0.00), top right point (10.00, 10.00) and "children" on lines 1, 2, 3.
  - 1 2 2 4 4 represents a "child" box contained by the parent box listed above, with the "child's" botto. left corner at (2.00,2.00) and its upper left corner at (4.00,4.00).

Examples:
  - ray: 0 0 1 1 intersects a box: 2 2 3 3
  - ray: -1 -1 1 0 does NOT intersect a box: 2 2 3 3

In addition to counting the number of intersections on each box, we must also:
  - check the map for correctness (I.E. no solid box overlap or "children" not fully contained by their "parents")
  - convert a non-numerical value inputted for slope to a vertical slope (for example: 0 0 Vertical 1 must be converted to a ray with a point of origin (0.00,0.00), Slope: NAN (not a number/undefined, usually the result of division by 0 as in the case of vertical slope), Direction: forwards (upwards in the case of a vertical slope).

TO-DO: 
   - optimize map-wide collision function, auto populate vector of parents within load map function (see main.cc).
