#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>
#include "WallLineClass.h"
#include "WallLineClass.cpp"
#include "LightLineClass.h"
#include "LightLineClass.cpp"

class MouseClass {
    public:
        int x;
        int y;
        int lastX;
        int lastY;
};
MouseClass mouse;

//start render window
int width = 700;
int height = 700;
sf::RenderWindow window(sf::VideoMode(width, height), "Ray Casting");

void drawLine(int sX, int sY, int fX, int fY) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(sX, sY)),
        sf::Vertex(sf::Vector2f(fX, fY))
    };

    window.draw(line, 2, sf::Lines);
}

//has to be summultiple of 360:
int numberOfRays = 360;

int numberOfWalls;
bool drawingMode = false;
bool light = true;
int main() {
    window.setFramerateLimit(60);
    std::vector<WallLineClass> wallClass;
    std::vector<LightLineClass> lightClass;

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        //get mouse pos
        sf::Vector2i tempxy = sf::Mouse::getPosition(window);
        mouse.x = tempxy.x;
        mouse.y = tempxy.y;

        if (mouse.x > 0 && mouse.x < width && mouse.y > 0 && mouse.y < height) {
            //clear screen
            window.clear(sf::Color::Black);


            //toggle drawing mode on/of
            if (sf:: Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (mouse.x >= 0 && mouse.x <= width && mouse.y >= 0 && mouse.y <= height) {
                    if (drawingMode == false) {
                        while (sf:: Mouse::isButtonPressed(sf::Mouse::Left)) {
                        }
                        mouse.lastX = mouse.x;
                        mouse.lastY = mouse.y;
                        drawingMode = true;
                    } else if (drawingMode == true) {
                        while (sf:: Mouse::isButtonPressed(sf::Mouse::Left)) {
                        }
                        //when done creating line save line
                        drawingMode = false;
                        WallLineClass newWall(mouse.lastX, mouse.lastY, mouse.x, mouse.y);
                        wallClass.push_back(newWall);
                    }
                }
            }
            if (sf:: Mouse::isButtonPressed(sf::Mouse::Right)) {
                if (mouse.x >= 0 && mouse.x <= width && mouse.y >= 0 && mouse.y <= height) {
                    if (light == false) {
                        while (sf:: Mouse::isButtonPressed(sf::Mouse::Right)) {
                        }
                        light = true;
                    } else if (light == true) {
                        while (sf:: Mouse::isButtonPressed(sf::Mouse::Right)) {
                        }
                        light = false;
                    }
                }

            }
            //draw walls
            numberOfWalls = wallClass.size();
            for (int i = 0; i < numberOfWalls; i++) {
                drawLine(wallClass[i].getStartX(), wallClass[i].getStartY(), wallClass[i].getFinishX(), wallClass[i].getFinishY());
            }
            //draw now drawn wall
            if (drawingMode == true) {
                drawLine(mouse.x, mouse.y, mouse.lastX, mouse.lastY);
            }

            //make rays
            for (int i = 0; i < numberOfRays; i++) {
                LightLineClass newRay(mouse.x, mouse.y, i, numberOfRays);
                lightClass.push_back(newRay);
            }
            //////////////////////////////////////////////////////
            //find intersections
            for (int i = 0; i < numberOfRays; i++) {
                for (int n = 0; n < numberOfWalls; n++) {
                    float p0x, p0y,   p1x, p1y;
                    float p2x, p2y,   p3x, p3y;
                    p0x = mouse.x;                      p0y = mouse.y;
                    p1x = lightClass[i].getFinishX();   p1y = lightClass[i].getFinishY();
                    p2x = wallClass[n].getStartX();     p2y = wallClass[n].getStartY();
                    p3x = wallClass[n].getFinishX();    p3y = wallClass[n].getFinishY();

                    float s1_x, s1_y, s2_x, s2_y;
                    s1_x = p1x - p0x;     s1_y = p1y - p0y;
                    s2_x = p3x - p2x;     s2_y = p3y - p2y;

                    float s, t;
                
                    s = (-s1_y * (p0x - p2x) + s1_x * (p0y - p2y)) / (s1_x * s2_y - s2_x * s1_y);
                    t = ( s2_x * (p0y - p2y) - s2_y * (p0x - p2x)) / (s1_x * s2_y -s2_x * s1_y);
                    
                    if (s > 0 && s < 1 && t > 0 && t < 1) {
                        //collision detected
                        float ix = p0x + (t * s1_x);
                        float iy = p0y + (t * s1_y);
                            
                        lightClass[i].setFinishX(ix);
                        lightClass[i].setFinishY(iy);
                    }
                    
                }

            }
            //draw rays
            if (light == true) {
                for (int i = 0; i < numberOfRays; i++) {
                    drawLine(mouse.x, mouse.y, lightClass[i].getFinishX(), lightClass[i].getFinishY());
                }
            }
            lightClass.clear();
            
        
            window.display();
        }

    }
}