#pragma once
#include <bits/stdc++.h>
#include "Base.cpp"

using namespace std;

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

Point2D projected(const Point3D &points, const OrthogonalSystem &system)
{
    Point2D projected;
    projected.x = system.d1[0] * points.x + system.d1[1] * points.y + system.d1[2] * points.z;
    projected.y = system.d2[0] * points.x + system.d2[1] * points.y + system.d2[2] * points.z;
    return projected;
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

Point3D find_max_z_max_x_min_y(const std::vector<Point3D> &points)
{
    Point3D result = points[0];

    for (const auto &p : points)
    {
        if (p.z > result.z)
        {
            result = p;
        }
        else if (p.z == result.z && p.x > result.x)
        {
            result = p;
        }
        else if (p.z == result.z && p.x == result.x && p.y < result.y)
        {
            result = p;
        }
    }

    return result;
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
    Point2D temp;
    for (Point2D p : Y)
    {
        if (p.x != y_star.x || p.y != y_star.y)
        { // dk1 y*!=y**
            bool check = true;
            for (Point2D q : Y)
            { // dk2 D(y*,y**,yi)>=0 with every i in I
                double D = Determenant(y_star, p, q);
                if (D < 0)
                {
                    check = false;
                }
            }
            if (check)
            {
                temp = p;
            }
        }
    }
    return temp;
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

// plain check
bool arePointsOnSamePlane(std::vector<Point3D> points)
{
    int n = points.size();
    if (n < 3)
    {
        // A plane must have at least 3 points
        return false;
    }

    // Compute centroid of points
    double x_mean = 0, y_mean = 0, z_mean = 0;
    for (int i = 0; i < n; i++)
    {
        x_mean += points[i].x;
        y_mean += points[i].y;
        z_mean += points[i].z;
    }
    x_mean /= n;
    y_mean /= n;
    z_mean /= n;

    // Compute the covariance matrix of the points
    double xx_cov = 0, yy_cov = 0, zz_cov = 0, xy_cov = 0, xz_cov = 0, yz_cov = 0;
    for (int i = 0; i < n; i++)
    {
        double x_diff = points[i].x - x_mean;
        double y_diff = points[i].y - y_mean;
        double z_diff = points[i].z - z_mean;
        xx_cov += x_diff * x_diff;
        yy_cov += y_diff * y_diff;
        zz_cov += z_diff * z_diff;
        xy_cov += x_diff * y_diff;
        xz_cov += x_diff * z_diff;
        yz_cov += y_diff * z_diff;
    }
    xx_cov /= n;
    yy_cov /= n;
    zz_cov /= n;
    xy_cov /= n;
    xz_cov /= n;
    yz_cov /= n;

    // Compute coefficients of plane equation
    double A = yy_cov * zz_cov - yz_cov * yz_cov;
    double B = xx_cov * zz_cov - xz_cov * xz_cov;
    double C = xx_cov * yy_cov - xy_cov * xy_cov;
    double D = -(A * x_mean + B * y_mean + C * z_mean);

    // Compute sum of squared distances from points to plane
    double sum_of_squares = 0;
    for (int i = 0; i < n; i++)
    {
        double distance = A * points[i].x + B * points[i].y + C * points[i].z + D;
        sum_of_squares += distance * distance;
    }

    // Compute the mean squared distance
    double mean_squares = sum_of_squares / n;

    // Define a threshold for mean squared distance
    double threshold = 1e-6;

    // If the mean squared distance is below the threshold,
    // the points are on the same plane
    return (mean_squares < threshold);
}