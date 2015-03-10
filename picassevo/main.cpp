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
#include <boost/program_options.hpp>
#include <boost/format.hpp>

#include "Individual/CircleIndividual.h"
#include "Individual/RectangleIndividual.h"
#include "Individual/SquareIndividual.h"
#include "Individual/TriangleIndividual.h"
#include "FitnessFunction.h"
#include "Evolver.h"
#include "Random.h"

Evolver* g_evolution;
unsigned g_image_width, g_image_height;
std::chrono::time_point<std::chrono::system_clock> g_last_update_time;
bool g_verbose;
int g_max_shapes;
std::string g_save_path;
int g_save_freq;

void save(AbstractIndividual const& individual, int index)
{
    int real_index = 0;
    
    if (g_save_freq > 0) {
        real_index = index;
    }
    
    lodepng::encode(boost::str(boost::format("%s/%09i.png") % g_save_path % real_index),
                    individual.get_pixels(),
                    individual.get_width(),
                    individual.get_height());
}

void run_evolution()
{
    if (g_max_shapes < 0 || g_evolution->get_num_successes() < g_max_shapes) {
        g_evolution->run(g_verbose);
        
        
        if (g_save_freq > 0 && g_evolution->get_num_successes() % g_save_freq == 0) {
            if (g_save_path != "") {
                save(g_evolution->get_best_individual(), g_evolution->get_num_successes());
            }
        }
        
        auto now = std::chrono::system_clock::now();
        auto seconds_since_last_update = now - g_last_update_time;
        
        if (seconds_since_last_update.count() > 1) {
            glutPostRedisplay();
        }
    } else {
        if (g_save_path != "") {
            save(g_evolution->get_best_individual(), g_evolution->get_num_successes());
        }
        glutIdleFunc(nullptr);
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
    
    std::string target_file_name;
    std::string shape;
    std::string bg_color;
    std::string save_path;
    int max_shapes;
    int save_freq;
    bool quiet;
    
    namespace po = boost::program_options;
    po::options_description options_desc("Allowed options");
    options_desc.add_options()
        ("help", "print a help message")
        ("target", po::value<std::string>(&target_file_name)->default_value("data/starry-night.png"),
            "target image (png only)")
        ("shape", po::value<std::string>(&shape)->default_value("circle"),
            "shape primitive to use")
        ("bg_color", po::value<std::string>(&bg_color)->default_value("black"),
            "background color (black or white)")
        ("max_shapes", po::value<int>(&max_shapes)->default_value(-1),
            "max number of shapes to draw (default: no limit)")
        ("save_path", po::value<std::string>(&save_path)->default_value(""),
            "folder to save result images (default: don't save)")
        ("save_freq", po::value<int>(&save_freq)->default_value(-1),
            "save every save_freq primitives (default: only save the last)")
        ("quiet,q", po::value<bool>(&quiet)->default_value(false)->implicit_value(true),
            "be quiet")
    ;
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, options_desc), vm);
    
    if (vm.count("help")) {
        std::cout << options_desc << std::endl;
        return 1;
    }
    
    po::notify(vm);
    
    if (bg_color != "black" && bg_color != "white") {
        std::cerr << "I don't understand bg_color='" << bg_color << "'" << std::endl;
        return 1;
    }
    
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
    
    std::unique_ptr<AbstractIndividual> individual;
    
    if (shape == "circle") {
        individual = std::make_unique<CircleIndividual>(fitness_function.get_width(),
                                                        fitness_function.get_height(),
                                                        bg_color);
    }
    else if (shape == "rectangle") {
        individual = std::make_unique<RectangleIndividual>(fitness_function.get_width(),
                                                           fitness_function.get_height(),
                                                           bg_color);
    }
    else if (shape == "triangle") {
        individual = std::make_unique<TriangleIndividual>(fitness_function.get_width(),
                                                          fitness_function.get_height(),
                                                          bg_color);
    }
    else if (shape == "square") {
        individual = std::make_unique<SquareIndividual>(fitness_function.get_width(),
                                                        fitness_function.get_height(),
                                                        bg_color);
    }
    else {
        std::cerr << "This is not a shape I recognize: '" << shape << "'" << std::endl;
        return 1;
    }
    
    Evolver evolution(*individual, &fitness_function);
    
    g_evolution = &evolution;
    g_last_update_time = std::chrono::system_clock::now();
    g_verbose = !quiet;
    g_max_shapes = max_shapes;
    g_save_path = save_path;
    g_save_freq = save_freq;
    
    glutMainLoop();
    
    return 0;
}
