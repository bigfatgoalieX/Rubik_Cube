#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;

class RubiksCube {
public:
    vector<vector<char>> front;
    vector<vector<char>> back;
    vector<vector<char>> left;
    vector<vector<char>> right;
    vector<vector<char>> up;
    vector<vector<char>> down;

    RubiksCube() {
        front = vector<vector<char>>(3, vector<char>(3, 'G')); // Green
        back = vector<vector<char>>(3, vector<char>(3, 'B'));  // Blue
        left = vector<vector<char>>(3, vector<char>(3, 'O'));  // Orange
        right = vector<vector<char>>(3, vector<char>(3, 'R')); // Red
        up = vector<vector<char>>(3, vector<char>(3, 'W'));    // White
        down = vector<vector<char>>(3, vector<char>(3, 'Y'));  // Yellow
    }

    void rotateFaceClockwise(vector<vector<char>>& face) {
        vector<vector<char>> temp = face;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                face[j][2 - i] = temp[i][j];
            }
        }
    }

    void rotateFrontClockwise() {
        rotateFaceClockwise(front);
        // Adjust adjacent edges
        vector<char> temp = {up[2][0], up[2][1], up[2][2]};
        up[2][0] = left[2][2];
        up[2][1] = left[1][2];
        up[2][2] = left[0][2];
        left[0][2] = down[0][0];
        left[1][2] = down[0][1];
        left[2][2] = down[0][2];
        down[0][0] = right[2][0];
        down[0][1] = right[1][0];
        down[0][2] = right[0][0];
        right[0][0] = temp[0];
        right[1][0] = temp[1];
        right[2][0] = temp[2];
    }

    void drawFace(sf::RenderWindow& window, vector<vector<char>>& face, int offsetX, int offsetY) {
        int size = 50;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                sf::RectangleShape square(sf::Vector2f(size, size));
                square.setPosition(offsetX + j * size, offsetY + i * size);
                square.setFillColor(getColor(face[i][j]));
                square.setOutlineThickness(1);
                square.setOutlineColor(sf::Color::Black);
                window.draw(square);
            }
        }
    }

    sf::Color getColor(char c) {
        switch (c) {
            case 'G': return sf::Color::Green;
            case 'B': return sf::Color::Blue;
            case 'O': return sf::Color(255, 165, 0); // Orange
            case 'R': return sf::Color::Red;
            case 'W': return sf::Color::White;
            case 'Y': return sf::Color::Yellow;
            default: return sf::Color::Black;
        }
    }

    void drawCube(sf::RenderWindow& window) {
        drawFace(window, front, 150, 150); // Center face
        drawFace(window, up, 150, 0);      // Top face
        drawFace(window, left, 0, 150);    // Left face
        drawFace(window, right, 300, 150); // Right face
        drawFace(window, down, 150, 300);  // Bottom face
        drawFace(window, back, 450, 150);  // Back face (for simplicity, drawn separately)
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Rubik's Cube Simulator");

    RubiksCube cube;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::F) {
                    cube.rotateFrontClockwise();
                }
            }
        }

        window.clear();
        cube.drawCube(window);
        window.display();
    }

    return 0;
}
