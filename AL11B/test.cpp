#include "Base.cpp"
#include "HelperFunc.cpp"

vector<Point2D> rotate_and_translate(vector<Point2D> &points, double angle, double dx, double dy)
{
    double sin_a = std::sin(angle);
    double cos_a = std::cos(angle);

    for (auto &p : points)
    {
        double x_new = p.x * cos_a - p.y * sin_a + dx;
        double y_new = p.x * sin_a + p.y * cos_a + dy;

        p.x = x_new;
        p.y = y_new;
    }
}

std::vector<Point2D> find_face(std::vector<Point2D> X)
{
    std::vector<Point2D> Y = X;
    Point2D y_star = find_lowest_y_highest_x(Y);
    Point2D y_star_star = find_y_star_star(y_star, Y);
    std::vector<int> I_star = find_I_star(Y, y_star, y_star_star);

    while (true)
    {
        vector<Point2D> xi_star;
        for (int i : I_star)
        {
            xi_star.push_back(Y[i]);
        }

        if (xi_star.size() == 1)
        {
            Point2D d1(1, 0), d2(0, 1), d3 = y_star_star - y_star;
            Y = rotate_and_translate(Y, d1, d2, d3);
            y_star = find_lowest_y_highest_x(Y);
            y_star_star = find_y_star_star(y_star, Y);
            I_star = find_I_star(Y, y_star, y_star_star);
        }
        else if (xi_star.size() == 2)
        {
            std::vector<Point2D> face_edges = find_face_edges(Y, I_star);
            return face_edges;
        }
        else
        {
            // Invalid input, return empty vector
            return std::vector<Point2D>();
        }
    }
}
