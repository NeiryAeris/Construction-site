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
    OrthogonalSystem idk = get_d1_d2(systemXY.d3);
    // Project the points from R^3 to R^2
    vector<Point2D> XYprojected = projectPoints(points, systemXY);
    // Fetch first point

    bool face_intitated = false;
    vector<Point3D> I_star;

    Point3D starting_point = find_max_z_max_x_min_y(points);
    Point2D y_star = projected(starting_point,systemXY);
    Point2D starry_y = find_y_star_star(y_star, XYprojected);
    for (int i = 0; i < number_of_points; i++)
    {
        if (Determenant(y_star, starry_y, XYprojected[i]) == 0)
        {
            I_star.push_back(points[i]);
        }
    }
    // I_star vis check
    // cout << "this is all the point in I_star" << endl;
    // for (auto &ptr : I_star)
    // {
    //     cout << ptr.x << " " << ptr.y << " " << ptr.z << " " << endl;
    // }

    int I_dim = compute_dimension(I_star);
    array<double, 3> temp_d3 = new_d3(y_star, starry_y, idk.d3);
    // if (I_dim == 1)
    // {
    //     systemXY.d3 = new_d3(starting_point, starry_y, temp_d3);
    //     _11b(points, number_of_points, systemXY);
    // }
    // else if (I_dim == 2)
    // {

    //     first_face = I_star;
    // }
    while (!arePointsOnSamePlane(I_star))
    {

        systemXY.d3 = new_d3(y_star, starry_y, temp_d3);

        // this thing need to escape condition
        _11b(points, number_of_points, systemXY);
    }
    first_face = I_star;
    face_intitated = true;
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
        cin >> input.x >> input.y >> input.z;
        points.push_back(input);
    }
    // vector<Point2D> XYprojected = projectPoints(points, systemXY);
    // Point2D starting_point = find_lowest_y_highest_x(XYprojected);
    // Point2D starry_y = find_y_star_star(starting_point, XYprojected);
    // cout << starting_point.x << " " << starting_point.y<<endl;
    // cout << starry_y.x << " " << starry_y.y;
    first_face = _11b(points, number_of_points, systemXY);
    for (auto ptr : first_face)
    {
        cout << ptr.x << " " << ptr.y << " " << ptr.z;
    }
    vector<Point2D> XYprojected = projectPoints(first_face, systemXY);
    convexHull(XYprojected, number_of_points);
    return 0;
}