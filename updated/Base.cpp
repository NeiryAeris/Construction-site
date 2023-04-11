#pragma once
#include <bits/stdc++.h>

using namespace std;

struct Point3D
{
    int tag_number;
    double x, y, z;
};

struct Point2D
{
    int tag_number2D;
    double x, y;
};

struct Edge
{
    int i1, i2;
    Point2D p1, p2;
    Point3D p1_, p2_;
};

struct Face
{
    int i1, i2, i3;
    Point2D p1, p2, p3;
    Point3D p1_, p2_, p3_;
};

struct OrthogonalSystem
{
    array<double, 3> d1;
    array<double, 3> d2;
    array<double, 3> d3;
};

array<double,3> new_d3(Point2D p1, Point2D p2, array<double,3> d3){
    
    d3[0] = p1.x-p2.x;
    d3[1] = p1.y- p2.y;
    return d3;
}