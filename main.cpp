#include "utils.h"
#include "Scene.h"

static int prevTime;
static Scene scene;

void init() {
  glClearColor(1.f, 0.f, 0.f, 1.f);

  scene.init();
}

static void drawCallback() {
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  scene.draw();

  glutSwapBuffers();
}

static void idleCallback() {
  unsigned int currentTime = glutGet(GLUT_ELAPSED_TIME);
  unsigned int deltaTime   = currentTime - prevTime;
	
  if(deltaTime > TIME_PER_FRAME) {
    // Every time we enter here is equivalent to a game loop execution  
    prevTime = currentTime;

    if (!scene.update(deltaTime))
      exit(0);

    glutPostRedisplay();
  }
}

static void keyboardDownCallback(unsigned char key, int x, int y) { scene.keyPressed(key); }
static void keyboardUpCallback(unsigned char key, int x, int y) { scene.keyReleased(key); }
static void motionCallback(int x, int y) { scene.mouseMove(x, y); }

int main(int argc, char* argv[]) {
  // GLUT initialization
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitContextVersion(4, 5);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  
  glutCreateWindow(argv[0]);
  glutDisplayFunc(drawCallback);
  glutIdleFunc(idleCallback);
  glutKeyboardFunc(keyboardDownCallback);
  glutKeyboardUpFunc(keyboardUpCallback);
  glutMotionFunc(motionCallback);
  
  // GLEW will take care of OpenGL extension functions
  glewExperimental = GL_TRUE;
  glewInit();

  init();
  
  glutMainLoop();

  return 0;
}
