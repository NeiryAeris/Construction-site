#include "Base.cpp"
#include "HelperFunc.cpp"
#include "Jarvis.cpp"

int main()
{
    // Get some points
    Point3D input;
    int number_of_points;
    vector<Point3D> points;
    cin >> number_of_points;
    for (int i = 0; i < number_of_points; i++)
    {
        input.tag_number = i;   //Name the points with numbers
        cin >> input.x >> input.y >> input.z;
        points.push_back(input);
    }

    // Define an orthogonal system in R^3
    OrthogonalSystem systemXY = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}};

    // Project the points from R^3 to R^2
    vector<Point2D> XYprojected = projectPoints(points, systemXY);
    //Fetch first point
    Point2D starting_point = find_lowest_y_highest_x(XYprojected);
    Point2D starry_y = find_y_star_star(starting_point,XYprojected);
    // Print the projected points
    for (const auto &point : XYprojected)
    {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }

    return 0;
}