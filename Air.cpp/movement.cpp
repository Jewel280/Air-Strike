#include <GL/glut.h>

GLfloat xTranslation = 0.0f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Translate the object
    glTranslatef(xTranslation, 0.0f, 0.0f);

    // Draw the object
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();

    // Swap buffers to display the rendered image
    glutSwapBuffers();
}

void update(int value) {
    // Update the translation value
    xTranslation += 0.01f;

    // Redraw the scene
    glutPostRedisplay();

    // Call update() again after a short delay
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Slow Translation");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}

