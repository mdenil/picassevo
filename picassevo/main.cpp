//
//  main.cpp
//  picassevo
//
//  Created by Misha Denil on 02/03/2015.
//  Copyright (c) 2015 Misha Denil. All rights reserved.
//

#include <GLUT/glut.h>

#include "lodepng/lodepng.h"

#include <vector>
#include <iostream>
#include <cassert>
#include <chrono>

#include "Individual/CircleIndividual.h"
#include "Individual/RectangleIndividual.h"
#include "Individual/TriangleIndividual.h"
#include "FitnessFunction.h"
#include "Evolver.h"
#include "Random.h"

struct Point {
    float position[2];
    float color[3];
    float intensity;
};


Evolver* g_evolution;
unsigned g_image_width, g_image_height;
std::chrono::time_point<std::chrono::system_clock> g_last_update_time;

void run_evolution()
{
    g_evolution->run();
    
    auto now = std::chrono::system_clock::now();
    auto seconds_since_last_update = now - g_last_update_time;
    
    if (seconds_since_last_update.count() > 1) {
        glutPostRedisplay();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    g_evolution->get_best_individual().draw();
    g_last_update_time = std::chrono::system_clock::now();
    glutSwapBuffers();
}


void reshape(int width, int height)
{
    glutReshapeWindow(g_image_width, g_image_height);
    
    glViewport(0, 0, g_image_width, g_image_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, g_image_width, g_image_height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    //std::string target_file_name = "data/isa.png";
    std::string target_file_name = "data/starry-night.png";
    //std::string target_file_name = "data/bridge.png";
    //std::string target_file_name = "data/explosion.png";
    //std::string target_file_name = "data/squares.png";
    //std::string target_file_name = "data/circles.png";
    //std::string target_file_name = "data/summer.png";
    
    FitnessFunction fitness_function(target_file_name);
    
    g_image_width = fitness_function.get_width();
    g_image_height = fitness_function.get_height();
    
    glutInitWindowSize(g_image_width, g_image_height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    glutCreateWindow("Picassevo");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(run_evolution);
    
    glClearColor(0,0,0,1);
    
    std::string individual_type = "circle";
    std::unique_ptr<AbstractIndividual> individual;
    
    if (individual_type == "circle") {
        individual = std::make_unique<CircleIndividual>(fitness_function.get_width(),
                                                        fitness_function.get_height());
    }
    else if (individual_type == "rectangle") {
        individual = std::make_unique<RectangleIndividual>(fitness_function.get_width(),
                                                           fitness_function.get_height());
    }
    else if (individual_type == "triangle") {
        individual = std::make_unique<TriangleIndividual>(fitness_function.get_width(),
                                                          fitness_function.get_height());
    }
    else {
        std::cerr << "This is not an individual_type: '" << individual_type << "'" << std::endl;
        return 1;
    }
    
    Evolver evolution(*individual, &fitness_function);
    
    g_evolution = &evolution;
    g_last_update_time = std::chrono::system_clock::now();
    
    glutMainLoop();
    
    return 0;
}
