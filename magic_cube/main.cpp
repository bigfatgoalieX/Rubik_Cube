#include <iostream>
#include <vector>

using namespace std;

class RubiksCube {
public:
    vector<vector<char>> front;
    vector<vector<char>> back;
    vector<vector<char>> left;
    vector<vector<char>> right;
    vector<vector<char>> up;
    vector<vector<char>> down;

    // constructor function   
    RubiksCube() {
        front = vector<vector<char>>(3, vector<char>(3, 'G')); // Green
        back = vector<vector<char>>(3, vector<char>(3, 'B'));  // Blue
        left = vector<vector<char>>(3, vector<char>(3, 'O'));  // Orange
        right = vector<vector<char>>(3, vector<char>(3, 'R')); // Red
        up = vector<vector<char>>(3, vector<char>(3, 'W'));    // White
        down = vector<vector<char>>(3, vector<char>(3, 'Y'));  // Yellow
    }

    // why '&'?
    // 为了避免拷贝，传递引用可以减少内存开销
    // 为了修改原始数据，传递引用可以直接修改原始数据
    void printFace(vector<vector<char>>& face) {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cout << face[i][j] << ' ';
            }
            cout << endl;
        }
    }

    void printCube() {
        cout << "Up:\n";
        printFace(up);
        cout << "Front:\n";
        printFace(front);
        cout << "Right:\n";
        printFace(right);
        cout << "Back:\n";
        printFace(back);
        cout << "Left:\n";
        printFace(left);
        cout << "Down:\n";
        printFace(down);
    }

    void rotateFaceClockwise(vector<vector<char>>& face) {
        vector<vector<char>> temp = face;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                face[j][2 - i] = temp[i][j];
            }
        }
    }

void rotateFaceEdgesClockwise(vector<vector<char>>& face, 
                                   vector<vector<char>>& up, int upRow, 
                                   vector<vector<char>>& right, int rightCol, 
                                   vector<vector<char>>& down, int downRow, 
                                   vector<vector<char>>& left, int leftCol) {
        vector<char> temp = {up[upRow][0], up[upRow][1], up[upRow][2]};

        up[upRow][0] = left[2][leftCol];
        up[upRow][1] = left[1][leftCol];
        up[upRow][2] = left[0][leftCol];

        left[0][leftCol] = down[downRow][0];
        left[1][leftCol] = down[downRow][1];
        left[2][leftCol] = down[downRow][2];

        down[downRow][0] = right[2][rightCol];
        down[downRow][1] = right[1][rightCol];
        down[downRow][2] = right[0][rightCol];

        right[0][rightCol] = temp[0];
        right[1][rightCol] = temp[1];
        right[2][rightCol] = temp[2];
    }

    void rotateFrontClockwise() {
        rotateFaceClockwise(front);
        rotateFaceEdgesClockwise(front, up, 2, right, 0, down, 0, left, 2);
    }

    void rotateBackClockwise() {
        rotateFaceClockwise(back);
        rotateFaceEdgesClockwise(back, up, 0, left, 0, down, 2, right, 2);
    }

    void rotateLeftClockwise() {
        rotateFaceClockwise(left);
        rotateFaceEdgesClockwise(left, up, 0, front, 0, down, 0, back, 2);
    }

    void rotateRightClockwise() {
        rotateFaceClockwise(right);
        rotateFaceEdgesClockwise(right, up, 2, back, 0, down, 2, front, 2);
    }

    void rotateUpClockwise() {
        rotateFaceClockwise(up);
        rotateFaceEdgesClockwise(up, back, 2, right, 0, front, 0, left, 0);
    }

    void rotateDownClockwise() {
        rotateFaceClockwise(down);
        rotateFaceEdgesClockwise(down, front, 2, right, 2, back, 0, left, 2);
    }

    void printFace(const vector<vector<char>>& face) {
        for (const auto& row : face) {
            for (const auto& elem : row) {
                cout << elem << ' ';
            }
            cout << endl;
        }
    }
};

int main() {
    RubiksCube cube;
    cube.printFace(cube.front);
    cout << "\nRotating front face clockwise...\n\n";
    cube.rotateFrontClockwise();
    cube.printCube();

    return 0;
}
