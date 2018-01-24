#include <cstdio>
#include <cstdlib>

#include "glut.h"

int oldx;
int oldy;

const float COLORS[][3] = {
  {1, 1, 1},
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1},
  {1, 1, 0},
  {1, 0, 1},
  {0, 1, 1},
  {0, 0, 0}
};

void checkGLErrors(const char* prefix) {
  GLenum error = glGetError();
  if(error != GL_NO_ERROR) {
    fprintf(stderr, "%s\n%s\n", prefix, gluErrorString(error));
    exit(-1);
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

  if(key >= '1' && key <= '8') {
    glColor3fv(COLORS[key - '1']);
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

int main(int argc, char **argv) {
  glutInit(&argc, argv);

  glutInitWindowSize(512, 512);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutCreateWindow("SimpleDraw");

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouseInput);
  glutMotionFunc(mouseMotion);

  int SIZE = 512 * 512 * 3;
  unsigned char data[SIZE];
  for(int i = 0; i < SIZE; ++i) {
    data[i] = i;
  }

  // glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(512, 512, GL_RGB, GL_UNSIGNED_BYTE, data);
  glutMainLoop();
}
