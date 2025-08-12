#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
using namespace glm;
using namespace std;

double c = 299792458.0;
double G = 6.67430e-11;

struct Ray;
void rk4Step(Ray &ray, double dλ, double rs);

struct Engine {
  GLFWwindow *window;
  int WIDTH = 800;
  int HEIGHT = 600;
  float width = 100000000000.0f; // Width of the viewport in meters
  float height = 75000000000.0f; // Height of the viewport in meters

  // Navigation state
  float offsetX = 0.0f, offsetY = 0.0f;
  float zoom = 1.0f;
  bool middleMousePressed = false;
  double lastMouseX = 0.0, lastMouseY = 0;

  Engine() {
    if (!glfwInit()) {
      cerr << "failed to initialise glfw" << endl;
      exit(EXIT_FAILURE);
    }
    window = glfwCreateWindow(WIDTH, HEIGHT, "2D Black Hole", NULL, NULL);
  }
}