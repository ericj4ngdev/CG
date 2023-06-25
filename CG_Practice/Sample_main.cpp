#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <GL/glut.h>

#define MAX_ROWS 100
#define MAX_COLS 100

int grid[MAX_ROWS][MAX_COLS];

const int WINDOW_SIZE = 500;
const int CELL_SIZE = 20;
int numRows = 0;
int numCols = 0;

void ReadMemoFile(const char* filename)
{
    FILE* file = NULL;
    if (fopen_s(&file, filename, "r"))
    {
        printf("Failed to open file: %s\n", filename);
        return;
    }

    char line[MAX_COLS];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';

        for (int i = 0; i < len; i++)
        {
            if (line[i] == '1')
                grid[numRows][i] = 1;
            else if (line[i] == '0')
                grid[numRows][i] = 0;
        }
        numRows++;
    }

    fclose(file);
}

void DrawGrid()
{
    glClear(GL_COLOR_BUFFER_BIT);

    int numRows = MAX_ROWS;
    int numCols = MAX_COLS;

    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            int color = grid[i][j];
            if (color == 1)
                glColor3f(0.0f, 0.0f, 0.0f); // 검은색
            else
                glColor3f(1.0f, 1.0f, 1.0f); // 흰색

            glBegin(GL_QUADS);
            glVertex2f(j * CELL_SIZE, i * CELL_SIZE);
            glVertex2f(j * CELL_SIZE, (i + 1) * CELL_SIZE);
            glVertex2f((j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
            glVertex2f((j + 1) * CELL_SIZE, i * CELL_SIZE);
            glEnd();
        }
    }

    glFlush();
}

void display()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // 배경을 흰색으로 지정
    glViewport(0, 0, WINDOW_SIZE, WINDOW_SIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_SIZE, 0, WINDOW_SIZE);

    DrawGrid();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
    glutCreateWindow("Memo Grid");
    glutDisplayFunc(display);

    ReadMemoFile("memo.txt");

    glutMainLoop();

    return 0;
}
