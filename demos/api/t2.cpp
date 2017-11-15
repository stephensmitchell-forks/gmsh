#include <gmsh.h>

// this reimplements gmsh/tutorial/t2.geo

int main(int argc, char **argv)
{
  gmshInitialize(argc, argv);
  gmshOptionSetNumber("General.Terminal", 1);

  gmshModelCreate("t2");

  // copy/paste from t1.cpp
  double lc = 1e-2;
  int o;
  gmshModelGeoAddPoint(1, 0, 0, 0, o, lc);
  gmshModelGeoAddPoint(2, .1, 0,  0, o, lc);
  gmshModelGeoAddPoint(3, .1, .3, 0, o, lc);
  gmshModelGeoAddPoint(4, 0,  .3, 0, o, lc);

  gmshModelGeoAddLine(1, 1, 2, o);
  gmshModelGeoAddLine(2, 3, 2, o);
  gmshModelGeoAddLine(3, 3, 4, o);
  gmshModelGeoAddLine(4, 4, 1, o);

  gmshModelGeoAddLineLoop(1, {4, 1, -2, 3}, o);
  gmshModelGeoAddPlaneSurface(1, {1}, o);
  gmshModelAddPhysicalGroup(0, 1, {1, 2});
  gmshModelAddPhysicalGroup(1, 2, {1, 2});
  gmshModelAddPhysicalGroup(2, 6, {1});
  gmshModelSetPhysicalName(2, 6, "My surface");
  // end copy/paste

  gmshModelGeoAddPoint(5, 0, .4, 0, o, lc);
  gmshModelGeoAddLine(5, 4, 5, o);
  gmshModelGeoTranslate({{0, 3}}, -0.05, 0, 0);

  std::vector<std::pair<int, int> > ov, ov2;
  gmshModelGeoCopy({{0, 3}}, ov);
  gmshModelGeoTranslate(ov, 0, 0.1, 0);

  gmshModelGeoAddLine(7, 3, ov[0].second, o);
  gmshModelGeoAddLine(8, ov[0].second, 5, o);
  gmshModelGeoAddLineLoop(10, {5,-8,-7,3}, o);
  gmshModelGeoAddPlaneSurface(11, {10}, o);

  gmshModelGeoCopy({{2, 1}, {2, 11}}, ov);
  gmshModelGeoTranslate(ov, 0.12, 0, 0);

  std::printf("New surfaces '%d' and '%d'\n", ov[0].second, ov[1].second);

  gmshModelGeoAddPoint(100, 0., 0.3, 0.13, o, lc);
  gmshModelGeoAddPoint(101, 0.08, 0.3, 0.1, o, lc);
  gmshModelGeoAddPoint(102, 0.08, 0.4, 0.1, o, lc);
  gmshModelGeoAddPoint(103, 0., 0.4, 0.13, o, lc);

  gmshModelGeoAddLine(110, 4, 100, o);
  gmshModelGeoAddLine(111, 3, 101, o);
  gmshModelGeoAddLine(112, 6, 102, o);
  gmshModelGeoAddLine(113, 5, 103, o);
  gmshModelGeoAddLine(114, 103, 100, o);
  gmshModelGeoAddLine(115, 100, 101, o);
  gmshModelGeoAddLine(116, 101, 102, o);
  gmshModelGeoAddLine(117, 102, 103, o);

  gmshModelGeoAddLineLoop(118, {115, -111, 3, 110}, o);
  gmshModelGeoAddPlaneSurface(119, {118}, o);
  gmshModelGeoAddLineLoop(120, {111, 116, -112, -7}, o);
  gmshModelGeoAddPlaneSurface(121, {120}, o);
  gmshModelGeoAddLineLoop(122, {112, 117, -113, -8}, o);
  gmshModelGeoAddPlaneSurface(123, {122}, o);
  gmshModelGeoAddLineLoop(124, {114, -110, 5, 113}, o);
  gmshModelGeoAddPlaneSurface(125, {124}, o);
  gmshModelGeoAddLineLoop(126, {115, 116, 117, 114}, o);
  gmshModelGeoAddPlaneSurface(127, {126}, o);

  gmshModelGeoAddSurfaceLoop(128, {127, 119, 121, 123, 125, 11}, o);
  gmshModelGeoAddVolume(129, {128}, o);

  gmshModelGeoExtrude({ov[1]}, 0, 0, 0.12, ov2);

  gmshModelGeoSetMeshSize({{0,103}, {0,105}, {0,109}, {0,102}, {0,28},
                           {0, 24}, {0,6}, {0,5}}, lc * 3);

  gmshModelAddPhysicalGroup(3, 1, {129,130});
  gmshModelSetPhysicalName(3, 1, "The volume");

  gmshModelGeoSynchronize();

  gmshModelMesh(3);

  gmshExport("t2.msh");

  gmshFinalize();
  return 0;
}