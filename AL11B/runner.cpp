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
        cin >> input.x >> input.y >> input.z;
        points.push_back(input);
    }
    
    // Define an orthogonal system in R^3
    OrthogonalSystem system = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}};

    // Project the points from R^3 to R^2
    vector<Point2D> XYprojected = projectPoints(points, system);

    // Print the projected points
    for (const auto &point : XYprojected)
    {
        cout << "(" << point.x << ", " << point.y << ")" << endl;
    }

    return 0;
}