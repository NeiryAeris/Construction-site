#include "Base.cpp"
#include "HelperFunc.cpp"
#include "Jarvis.cpp"
vector<Point3D> first_face;
// Define an orthogonal system in R^3
OrthogonalSystem systemXY = {
    {1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {0.0, 0.0, 1.0}};

vector<Point3D> _11b(const vector<Point3D> points, int number_of_points, OrthogonalSystem systemXY)
{
    get_d1_d2(systemXY.d3);
    // Project the points from R^3 to R^2
    vector<Point2D> XYprojected = projectPoints(points, systemXY);
    // Fetch first point

    bool face_intitated = false;
    vector<Point3D> I_star;

    Point2D starting_point = find_lowest_y_highest_x(XYprojected);
    Point2D starry_y = find_y_star_star(starting_point, XYprojected);
    for (int i = 0; i < number_of_points; i++)
    {
        if (Determenant(starting_point, starry_y, XYprojected[i]) == 0)
        {
            I_star.push_back(points[i]);
        }
    }
    int I_dim = compute_dimension(I_star);
    array<double, 3> temp_d3;
    if (I_dim == 1)
    {
        systemXY.d3 = new_d3(starting_point, starry_y, temp_d3);
        _11b(points, number_of_points, systemXY);
    }
    else if (I_dim == 2)
    {

        first_face = I_star;
    }
    return first_face;
}
int main()
{
    // Get some points
    Point3D input;
    int number_of_points;
    vector<Point3D> points;
    cin >> number_of_points;
    for (int i = 0; i < number_of_points; i++)
    {
        input.tag_number = i; // Name the points with numbers
        cin >> input.x >> input.y >> input.z;
        points.push_back(input);
    }
    first_face =_11b(points, number_of_points, systemXY);
    for (auto ptr: first_face){
        cout << ptr.x << " "<<ptr.y << " "<<ptr.z;
    }
    vector<Point2D> XYprojected = projectPoints(first_face, systemXY);
    convexHull(XYprojected, number_of_points);
    return 0;
}