#include <cstdio>
#include <cstdlib>

#include "glut.h"
#include "image.h"

const float COLORS[][3] = {
  {0.0, 0.0, 0.0},
  {1.0, 1.0, 1.0},
  {1.0, 0.0, 0.0},
  {0.0, 1.0, 0.0},
  {0.0, 0.0, 1.0},
  {0.0, 1.0, 1.0},
  {1.0, 0.0, 1.0},
  {1.0, 1.0, 0.0},
  {1.0, 0.5, 0.0},
  {0.5, 0.5, 0.5}
};

const char NAMES[][8] = {
  "Black",
  "White",
  "Red",
  "Green",
  "Blue",
  "Cyan",
  "Magenta",
  "Yellow",
  "Orange",
  "Grey"
};

int oldx;
int oldy;

void checkGLErrors(const char* prefix) {
  GLenum error = glGetError();
  if(error != GL_NO_ERROR) {
    fprintf(stderr, "%s\n%s\n", prefix, gluErrorString(error));
    exit(1);
  }
}

void display(void) {
  checkGLErrors("Errors in display()!");
  glutSwapBuffers();
}

void keyboard(unsigned char key, int, int) {
  if(key == 27 || key == 'q' || key == 'Q') {
    exit(0);
  }
  else if(key >= '0' && key <= '9') {
    char buffer[32];
    glColor3fv(COLORS[key - '0']);
    sprintf(buffer, "SimpleDraw: %s", NAMES[key - '0']);
    glutSetWindowTitle(buffer);
    
  }
  else if(key == 'w' || key == 'W') {
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    int w = glutGet(GLUT_WINDOW_WIDTH);

    Image image(w, h);
    glReadPixels(0, 0, w, h, GL_BGR, GL_UNSIGNED_BYTE, image.data());
    save_bmp("SimpleDraw.bmp", image);
  }
  else if(key == ' ') {
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
  }
}

void mouseInput(int button, int state, int x, int y) {
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    oldx = x;
    oldy = y;
  }
}

void mouseMotion(int x, int y) {
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  int w = glutGet(GLUT_WINDOW_WIDTH);

  glBegin(GL_LINES);
  glVertex2f(2 * float(oldx) / w - 1, 2 * float(-oldy) / h + 1);
  glVertex2f(2 * float(x)    / w - 1, 2 * float(-y)    / h + 1);
  glEnd();

  glutPostRedisplay();
  oldx = x;
  oldy = y;
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

  if(argc > 1) {
    Image image = load_bmp(argv[1]);
    glutInitWindowSize(image.width(), image.height());
    glutCreateWindow("SimpleDraw: White");
    glDrawPixels(image.width(), image.height(), GL_BGR, GL_UNSIGNED_BYTE, image.data());
  }
  else {
    glutInitWindowSize(512, 512);
    glutCreateWindow("SimpleDraw: White");
    glClear(GL_COLOR_BUFFER_BIT);
  }

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouseInput);
  glutMotionFunc(mouseMotion);

  glutMainLoop();
}
