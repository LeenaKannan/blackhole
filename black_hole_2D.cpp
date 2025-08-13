#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
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
    if (!window) {
      cerr << "failed to create glfw window" << endl;
      glfwTerminate();
      exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
      cerr < "failed to initialise glew" << endl;
      glewDestroyWindow(window);
      glewTerminate();
      exit(EXIT_FAILURE);
    }
    glViewport(0, 0, WIDTH, HEIGHT);
  }
  void run() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double left = -width + offsetX;
    double right = width + offsetX;
    double bottom = -height + offsetY;
    double top = height + offsetY;
    glOrtho(left, right, bottom, top, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
};

struct BlackHole {
  vec3 position;
  double mass;
  double radius;
  double r_s;

  BlackHole(vec3 pos, float m) : position(pos), mass(m) {
    r_s = 2.0 * G * mass / (c * c);
  }
  void draw() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    for (int i = 0; i <= 100; i++) {
      float angle = 2.0f * M_PI * i / 100;
      float x = r_s * sin(angle);
      float y = r_s * cos(angle);
      glVertex2f(x, y);
    }
    glEnd();
  }
};
BlackHole SagA(vec3(0.0f, 0.0f, 0.0f), 8.54e36);

struct Ray {
  // cartesian coordinates
  double x, y;
  // polar coordinates
  double r, phi, dr, dphi;

  vector<vec2> trail; // trail of points
  double E, L;        // conserved quanitites

  Ray(vec2 pos, vec2 dir)
      : x(pos.x), y(pos.y), r(sqrt(pos.x * pos.x + pos.y * pos.y)),
        phi(atan2(pos.y, pos.x)), dr(dir.x), dphi(dir.y) {
    this->r = sqrt(x * x + y * y);
    this->phi = atan2(y, x);
    dr = dir.x * cos(phi) + dir.y * sin(phi);
    dphi = (-dir.x * sin(phi) + dir.y * cos(phi)) / r;
    L = r * r * dphi;
    double f = 1.0 - SagA.r_s / r;
    double dt_dλ = sqrt((dr * dr) / (f * f) + (r * r * dphi * dphi) / f);
    E = f * dt_dλ;
    trail.push_back({x, y});
  }
  void draw(const std::vector<Ray> &rays) {
    // draw current ray positions as points
    glPointsize(2.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    for (auto &ray : rays) {
      ray.step(1.0f)
    }

    if (r <= r_s) {
      // less than swarzschild radius
    }
  };
  vector<Ray> rays;

  int main() {
    while (!glfwWindowShouldClose(engine.window)) {
      engine.run();
      SagA.draw();

      for (auto &ray : rays) {
        ray.step(1.0f, )
      }
    }
  }