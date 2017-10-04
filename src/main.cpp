
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

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  double mouse[2];

  while(!glfwWindowShouldClose(window)) {

    double nmouse[2];
    glfwGetCursorPos(window, &nmouse[0], &nmouse[1]);

    double mouseDelta[2] = {nmouse[0] - mouse[0], nmouse[1] - mouse[1]};

    mouse[0] = nmouse[0]; mouse[1] = nmouse[1];

    int width, height;

    glfwGetFramebufferSize(window, &width, &height);

    glClearColor(0.3, 0.7, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90, width / (float) height, 0.1, 1000.0);
    float x = sin(glfwGetTime() * 0.1) * 20;
    float y = cos(glfwGetTime() * 0.1) * 20;
    gluLookAt(0, 0, 0, 1, 0, 0, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    w->draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete w;
  delete tex;

  glfwDestroyWindow(window);
  glfwTerminate();
};
