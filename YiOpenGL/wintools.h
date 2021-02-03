#ifndef WINTOOLS_H_
#define WINTOOLS_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/camera.h>
#include "global.h"

#include <stb_image.h>

extern Camera camera;

// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 1000;

// timing
extern float deltaTime;	// time between current frame and last frame
extern float lastFrame;


//³õÊ¼»¯´°¿Ú
GLFWwindow* initWin();

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window);

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

extern unsigned int loadTexture(char const *path);

#endif