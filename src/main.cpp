
#include <X11/Xlib.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#include <stdlib.h>

#include "texture.h"

int main(int argc, char **argv) {
  if(!glfwInit()) {
    return 1;
  }

  GLFWwindow* window = glfwCreateWindow(640, 480, "RESIDUE", NULL, NULL);

  glfwMakeContextCurrent(window);

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.75, 0.75, 0.75, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  while(!glfwWindowShouldClose(window)) {

    int width, height;

    glfwGetFramebufferSize(window, &width, &height);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  glfwTerminate();
};
