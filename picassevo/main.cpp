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
#include "Painter.h"
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

Painter* g_painter;
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
    
    //FitnessFunction fitness_function("data/lisa.png");
    //FitnessFunction fitness_function("data/starry-night.png");
    FitnessFunction fitness_function("data/bridge.png");
    //FitnessFunction fitness_function("data/bbd1.png");
    
    image_width = fitness_function.get_width();
    image_height = fitness_function.get_height();
    
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
    Painter painter;
    Evolver evolution(individual, &painter, &fitness_function);
    
    g_painter = &painter;
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
    /*
     glClear(GL_COLOR_BUFFER_BIT);
     
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
     //glEnable(GL_ALPHA_TEST);
     //glDisable(GL_ALPHA_TEST);
     
     Individual individual(image_width, image_height);
     Painter painter;
     FitnessFunction fitness_function("lisa.png");
     
     //painter.paint(individual);
     
     std::cout << fitness_function.evaluate(individual, &painter) << std::endl;
     */

    g_last_update_time = std::chrono::system_clock::now();
    
    g_painter->paint(g_evolution->get_best_individual());
    
    glutSwapBuffers();
}



void display_image()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    // https://github.com/lvandeve/lodepng/blob/master/examples/example_opengl.cpp
    
    glViewport(0, 0, image_width, image_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, image_width, image_height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    //glDisable(GL_ALPHA_TEST);
    
    // I'm gonna give no fucks about power of two sized textures
    
    glEnable(GL_TEXTURE_2D);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 image_width,
                 image_height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 (void*)image.data());
    
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2f(0, 0);
    glTexCoord2d(1, 0); glVertex2f(image_width, 0);
    glTexCoord2d(1, 1); glVertex2f(image_width, image_height);
    glTexCoord2d(0, 1); glVertex2f(0, image_height);
    glEnd();

    glutSwapBuffers();
    
    // now get the pixels
    
    std::vector<unsigned char> pixels;
    pixels.resize(image_width * image_height * 4);
    
    glReadPixels(0, 0, image_width, image_height, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    
    // turn the pixels upside down or something
    for (int i = 0; i < image_width; ++i) {
        for (int j = 0; j < image_height; ++j) {
            for (int c = 0; c < 4; ++c) {
                std::swap(pixels[i*image_height*4 + j*4 + c],
                          pixels[i*image_height*4 + (image_height-j-1)*4 + c]);
            }
        }
    }
    
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 image_width,
                 image_height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 (void*)pixels.data());
    
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex2f(0, 0);
    glTexCoord2d(1, 0); glVertex2f(image_width, 0);
    glTexCoord2d(1, 1); glVertex2f(image_width, image_height);
    glTexCoord2d(0, 1); glVertex2f(0, image_height);
    glEnd();
    
    glutSwapBuffers();
    
}



/*! glut reshape callback function.  GLUT calls this function whenever
 the window is resized, including the first time it is created.
 You can use variables to keep track the current window size.
 */
void reshape(int width, int height)
{
    glutReshapeWindow(image_width, image_height);
    
    /* tell OpenGL we want to display in a recangle that is the
     same size as the window
     */
    glViewport(0,0,width,height);
    
    /* switch to the projection matrix */
    glMatrixMode(GL_PROJECTION);
    
    /* clear the projection matrix */
    glLoadIdentity();
    
    /* set the camera view, orthographic projection in 2D */
    gluOrtho2D(0,width,0,height);
    
    /* switch back to the model view matrix */
    glMatrixMode(GL_MODELVIEW);
    
    
    
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