#include <bits/stdc++.h>

using namespace std;

struct Point
{
    double x, y;
};

double cross_product(Point p, Point q, Point r)
{
    double pq_x = q.x - p.x;
    double pq_y = q.y - p.y;
    double pr_x = r.x - p.x;
    double pr_y = r.y - p.y;
    return pq_x * pr_y - pq_y * pr_x;
}

bool is_on_right(vector<Point> points, Point p, Point q)
{
    for (Point r : points)
    {
        if (r.x != p.x && r.y != p.y && r.x != q.x && r.y != q.y)
        {
            double cp = cross_product(p, q, r);
            if (cp >= 0)
            {
                return false;
            }
        }
    }
    return true;
}

int main() {
    vector<Point> points = {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}};
    Point edge_p, edge_q;

    for (Point p : points) {
        for (Point q : points) {
            if (p.x != q.x || p.y != q.y) {
                if (is_on_right(points, p, q)) {
                    edge_p = p;
                    edge_q = q;
                    break;
                }
            }
        }
    }

    cout << "The edge on the right side is (" << edge_p.x << ", " << edge_p.y << ") to (" << edge_q.x << ", " << edge_q.y << ")" << endl;

    return 0;
}
