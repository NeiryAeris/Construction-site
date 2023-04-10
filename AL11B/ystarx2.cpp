#include <iostream>
#include <vector>

using namespace std;

// Define the orthogonal system d1, d2, d3
vector<vector<double>> d = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

// Define the function D(y1, y2, y3) = det([y1; y2; y3])
double D(vector<double> y1, vector<double> y2, vector<double> y3) {
    return y1[0] * (y2[1] * y3[2] - y2[2] * y3[1])
         - y1[1] * (y2[0] * y3[2] - y2[2] * y3[0])
         + y1[2] * (y2[0] * y3[1] - y2[1] * y3[0]);
}

// Function to find Yi* and Yi**
pair<int, int> find_Y_star(vector<vector<double>> Y) {
    int n = Y.size();
    int ymax = Y[0][1], ymin = Y[0][1], ymax_index = 0;
    for (int i = 1; i < n; i++) {
        if (Y[i][1] > ymax) {
            ymax = Y[i][1];
            ymax_index = i;
        } else if (Y[i][1] == ymax && Y[i][0] > Y[ymax_index][0]) {
            ymax_index = i;
        }
        if (Y[i][1] < ymin) ymin = Y[i][1];
    }
    int ystar_index = ymax_index, ystarstar_index = 0;
    double dmax = -1;
    for (int i = 0; i < n; i++) {
        if (i == ystar_index) continue;
        double d = D(Y[ystar_index], Y[i], Y[ystar_index + 1]);
        if (d >= 0) {
            if (d > dmax) {
                dmax = d;
                ystarstar_index = i;
            }
        }
    }
    vector<int> I_star;
    for (int i = 0; i < n; i++) {
        if (D(Y[ystar_index], Y[ystarstar_index], Y[i]) == 0) {
            I_star.push_back(i);
        }
    }
    return make_pair(ystar_index, ystarstar_index);
}

int main() {
    // Example usage
    vector<vector<double>> Y = {{0, 0}, {1, 0}, {2, 1}, {1, 2}, {0, 1}};
    auto result = find_Y_star(Y);
    cout << "Yi* index: " << result.first << endl;
    cout << "Yi** index: " << result.second << endl;
    return 0;
}
