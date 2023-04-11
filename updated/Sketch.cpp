#include <iostream>
#include <cmath>
#include <vector>

struct Point3D
{
    double x, y, z;
};

// Helper function to compute the dot product of two 3D vectors
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
    Point3D q = {p.x / n, p.y / n, p.z / n};
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

int main()
{
    // Example set of points in 3D space
    std::vector<Point3D> points = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
    };

    // Compute the dimension of the subspace spanned by the points
    int dim = compute_dimension(points);

    std::cout << "The set of points has dimension " << dim << std::endl;

    return 0;
}
