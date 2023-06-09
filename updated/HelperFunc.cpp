#pragma once
#include <bits/stdc++.h>
#include "Base.cpp"

using namespace std;

// bool collinear(Point3D p1, Point3D p2, Point3D p3)
// {
//     // Compute the cross product of vectors p1p2 and p1p3
//     Point3D v1 = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
//     Point3D v2 = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
//     double cx = v1.y * v2.z - v1.z * v2.y;
//     double cy = v1.z * v2.x - v1.x * v2.z;
//     double cz = v1.x * v2.y - v1.y * v2.x;
//     // Check if the cross product is (approximately) zero
//     double epsilon = 1e-9;
//     return (abs(cx) < epsilon && abs(cy) < epsilon && abs(cz) < epsilon);
// }

// Point2D project(Point3D p, Point3D origin, Point3D d1, Point3D d2)
// {
//     Point3D u = {p.x - origin.x, p.y - origin.y, p.z - origin.z};
//     double x = d1.x * u.x + d1.y * u.y + d1.z * u.z;
//     double y = d2.x * u.x + d2.y * u.y + d2.z * u.z;
//     return {x, y};
// }

// Project points from R^3 to R^2 using the transformation yi = [d^T1 * xi, d^T2 * xi]^T
vector<Point2D> projectPoints(const vector<Point3D> &points, const OrthogonalSystem &system)
{
    vector<Point2D> projectedPoints;
    for (const auto &point : points)
    {
        Point2D projectedPoint;
        projectedPoint.x = system.d1[0] * point.x + system.d1[1] * point.y + system.d1[2] * point.z;
        projectedPoint.y = system.d2[0] * point.x + system.d2[1] * point.y + system.d2[2] * point.z;
        projectedPoints.push_back(projectedPoint);
    }
    return projectedPoints;
}

set<Face> Faces;

Point2D find_lowest_y_highest_x(const vector<Point2D> &points)
{
    Point2D lowest_y = points[0];
    for (const Point2D &p : points)
    {
        if (p.y < lowest_y.y)
        {
            lowest_y = p;
        }
        else if (p.y == lowest_y.y && p.x > lowest_y.x)
        {
            lowest_y = p;
        }
    }
    return lowest_y;
}

// Define the function D(y1, y2, y3) = det([y1; y2; y3])
double Determenant(Point2D y1, Point2D y2, Point2D y3)
{
    return y1.x * y2.y + y2.x * y3.y + y3.x * y1.y - y3.x * y2.y - y1.x * y3.y - y2.x * y1.y;
}
// Picking orthogonal system
OrthogonalSystem get_d1_d2(const array<double, 3> &d3)
{
    OrthogonalSystem d;
    d.d1.fill(0);
    d.d2.fill(0);
    d.d3.fill(0);

    // Case 1: d3[1] = d3[2] = 0
    if (d3[1] == 0 && d3[2] == 0)
    {
        d.d1[1] = 1; // set d1=(010)
        d.d2[2] = 1; // set d2=(001)
    }
    // Case 2: d3[1] = 0 and d3[2] != 0
    else if (d3[1] == 0 && d3[2] != 0)
    {
        d.d1[1] = 1;
        d.d2[0] = 1;
        d.d2[1] = -d3[0] / d3[2];
    }
    // Case 3: d3[1]!=0 and d3[2] = 0
    else if (d3[1] != 0 && d3[2] == 0)
    {
        d.d1[2] = 1;
        d.d2[0] = 1;
        d.d2[1] = -d3[0] / d3[1];
    }
    // Case 4: d3[1] != 0 and d3[2] != 0
    else
    {
        d.d1[1] = -d3[2] / d3[1];
        d.d1[2] = 1;
        double denom = d3[1] * d3[1] + d3[2] * d3[2];
        d.d2[0] = 1;
        d.d2[1] = -d3[0] * d3[1] / denom;
        d.d2[2] = -d3[0] * d3[2] / denom;
    }

    d.d3 = d3;

    return d;
}
// Finding starry Y
// Point2D* find_y_star_star(Point2D* y_star, std::vector<Point2D*> Y) {
//     Point2D* y_star_star = nullptr;
//     for (Point2D* p : Y) {
//         if (p->y == y_star->y && p->x != y_star->x) {
//             continue;
//         }
//         if (y_star_star == nullptr) {
//             y_star_star = p;
//         } else {
//             double D = Determenant(y_star, y_star_star, p);//this is where errors occur
//             if (D >= 0) {
//                 y_star_star = p;
//             }
//         }
//     }
//     return y_star_star;
// }

Point2D find_y_star_star(Point2D y_star, std::vector<Point2D> Y)
{
    Point2D y_star_star;
    bool y_star_star_initialized = false;
    for (Point2D p : Y)
    {
        if (p.y == y_star.y && p.x != y_star.x)
        {
            continue;
        }
        if (!y_star_star_initialized)
        {
            y_star_star = p;
            y_star_star_initialized = true;
        }
        else
        {
            double D = Determenant(y_star, y_star_star, p);
            if (D >= 0)
            {
                y_star_star = p;
            }
        }
    }
    return y_star_star;
}
// This is for calculating DIM
double dot_product(const Point3D &p1, const Point3D &p2)
{
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

// Helper function to compute the norm of a 3D vector
double norm(const Point3D &p)
{
    return std::sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

// Helper function to normalize a 3D vector
Point3D normalize(const Point3D &p)
{
    double n = norm(p);
    Point3D q;
    q.x = p.x / n;
    q.y = p.y / n;
    q.z = p.z / n;
    return q;
}

// Function to compute the dimension of the subspace spanned by a set of points
int compute_dimension(const std::vector<Point3D> &points)
{
    // Use Gram-Schmidt to orthogonalize the set of points
    std::vector<Point3D> basis;
    for (const Point3D &p : points)
    {
        Point3D q = p;
        for (const Point3D &b : basis)
        {
            double dot = dot_product(p, b);
            q.x -= dot * b.x;
            q.y -= dot * b.y;
            q.z -= dot * b.z;
        }
        if (norm(q) > 1e-10)
        {
            basis.push_back(normalize(q));
        }
    }

    // The dimension is equal to the number of nonzero vectors in the orthonormal basis
    int dim = basis.size();

    return dim;
}