#include <GL/glut.h>
#include <iostream>
#include <string>

float deltaTime = 0.0f;
float lastFrame = 0.0f;

std::string FormatTime(int seconds) {
    int hours = seconds / 3600; seconds %= 3600;
    int minutes = seconds / 60; seconds %= 60;

    std::string time;
    time += (hours < 10 ? "0" : "") + std::to_string(hours) + ":";
    time += (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":";
    time += (seconds < 10 ? "0" : "") + std::to_string(seconds);
    return time;
}

void TimeCalculation() {
    float crntFrame = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
    deltaTime = crntFrame - lastFrame;
    lastFrame = crntFrame;

    // Calculate time in frames
    int timeNow = (int)round(crntFrame * 60);

    // Format and render time
    std::string formattedTime = FormatTime(timeNow);
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(10.0f, 10.0f); // Adjust the values as needed
    for (char c : formattedTime) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
    }
}

void renderScene()
{
    // Render background
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Reset transformations
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480); // Adjust the values as needed

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Time calculation
    TimeCalculation();    

    // Swap buffers
    glutSwapBuffers();
}

void update(int value)
{
    // Call the render function
    renderScene();
    std::cout << deltaTime << " \n";
    // Register the next update
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(480, 480);
    glutCreateWindow("Simple OpenGL Window");

    glutDisplayFunc(renderScene);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();

    return 0;
}
