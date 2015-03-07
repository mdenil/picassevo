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

#include "OriginalIndividual.h"
#include "CircleIndividual.h"
#include "FitnessFunction.h"
#include "Evolver.h"
#include "Random.h"

struct Point {
    float position[2];
    float color[3];
    float intensity;
};


std::vector<unsigned char> image;
unsigned image_width, image_height;

Evolver* g_evolution;
std::chrono::time_point<std::chrono::system_clock> g_last_update_time;


/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);

void run_evolution();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    FitnessFunction fitness_function("data/lisa.png");
    //FitnessFunction fitness_function("data/starry-night.png");
    //FitnessFunction fitness_function("data/bridge.png");
    //FitnessFunction fitness_function("data/explosion.png");
    //FitnessFunction fitness_function("data/squares.png");
    
    image_width = fitness_function.get_width();
    image_height = fitness_function.get_height();
    
    image = fitness_function.get_target();
    
    glutInitWindowSize(image_width, image_height);
    

    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    
    /* create the window (and call it Lab 1) */
    glutCreateWindow("Picassevo");
    
    /* set the glut display callback function
     this is the function GLUT will call every time
     the window needs to be drawn
     */
    glutDisplayFunc(display);
    
    /* set the glut reshape callback function
     this is the function GLUT will call whenever
     the window is resized, including when it is
     first created
     */
    glutReshapeFunc(reshape);
    
    /* set the default background color to black */
    glClearColor(0,0,0,1);

    glutIdleFunc(run_evolution);

    
    CircleIndividual individual(fitness_function.get_width(), fitness_function.get_height());
    Evolver evolution(individual, &fitness_function);
    
    g_evolution = &evolution;
    g_last_update_time = std::chrono::system_clock::now();

    
    
    /* enter the main event loop so that GLUT can process
     all of the window event messages
     */
    glutMainLoop();
    
    return 0;
}

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


/*! glut reshape callback function.  GLUT calls this function whenever
 the window is resized, including the first time it is created.
 You can use variables to keep track the current window size.
 */
void reshape(int width, int height)
{
    glutReshapeWindow(image_width, image_height);
    
    glViewport(0, 0, image_width, image_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, image_width, image_height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}