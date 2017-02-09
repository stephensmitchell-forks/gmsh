SetFactory("OpenCASCADE");

Mesh.Algorithm = 6;
Mesh.CharacteristicLengthMin = 0.1;
Mesh.CharacteristicLengthMax = 0.1;

Point(1) = {0,0,0};
Point(2) = {1,0,0};
Point(3) = {1,1,0};
Point(4) = {0,1,0};
Point(5) = {0.5,0.5,1};
Line(1) = {1,2};
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,1};
Line(5) = {1,5};
Line(6) = {2,5};
Line(7) = {3,5};
Line(8) = {4,5};
Line Loop(1) = {1,2,3,4};
Line Loop(2) = {1,5,6};
Line Loop(3) = {2,6,7};
Line Loop(4) = {3,7,8};
Line Loop(5) = {4,5,8};
Plane Surface(1) = {1};
Plane Surface(2) = {2};
Plane Surface(3) = {3};
Plane Surface(4) = {4};
Plane Surface(5) = {5};
Surface Loop(1) = {1,2,3,4,5};
Volume(1) = {1};

Cylinder(2) = {0.5,0.5,-0.5, 0.5,0.5,1.5, 0.2};
BooleanFragments{ Volume{1}; Delete; }{ Volume{2}; Delete; }

// FIXME: need to delete surfaces 1:4, as they were bound to tags before the
// boolean operation