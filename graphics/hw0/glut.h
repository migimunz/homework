#ifndef GLUT_AUTOLOADER
#define GLUT_AUTOLOADER

#if defined DARWIN
#include <GLUT/glut.h>
// GLUT seems to be on its way out...
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined LINUX
#include <GL/glut.h>
#endif

#endif
