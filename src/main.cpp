
#include <X11/Xlib.h>

#define GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdlib.h>
#include <cmath>

#include "texture.h"
#include "chunk.h"
#include "world.h"

int main(int argc, char **argv) {
  if(!glfwInit()) {
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

  GLFWwindow* window = glfwCreateWindow(640, 480, "RESIDUE", nullptr, nullptr);
  if(window == NULL) {
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);

  Texture *tex = new Texture("assets/blocks/dirt.png");
  tex->bind();

  World *w = new World();

  while(!glfwWindowShouldClose(window)) {

    int width, height;

    glfwGetFramebufferSize(window, &width, &height);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, width / (float) height, 0.1, 1000.0);
    float x = sin(glfwGetTime()) * 40;
    float y = cos(glfwGetTime()) * 40;
    gluLookAt(x, y, 80, 0, 0, 64, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    w->draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete w;

  glfwTerminate();
};
