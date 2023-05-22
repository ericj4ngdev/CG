#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <vector>


using namespace std;

int screenWidth = 480;
int screenHeight = 480;
GLuint programID;
GLuint vertexBufferID[2];
GLuint VertexArrayID[2];

vector <float> g_points;
vector <float> g_colors;

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
	//create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	//Read the vertex shader code from the file
	string VertexShaderCode;
	ifstream VertexShaderStream(vertex_file_path, ios::in);
	if (VertexShaderStream.is_open())
	{
		string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}

	//Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	//Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		vector<char> VertexShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
	}
	//Read the fragment shader code from the file
	string FragmentShaderCode;
	ifstream FragmentShaderStream(fragment_file_path, ios::in);
	if (FragmentShaderStream.is_open())
	{
		string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	//Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const* FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	//Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		vector<char> FragmentShaderErrorMessage(InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
	}
	//Link the program
	fprintf(stdout, "Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	vector<char> ProgramErrorMessage(max(InfoLogLength, int(1)));
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
	fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void myMouseFn(int button, int state, int x, int y)
{
	float myX, myY;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		// normalize coordinate (3D-> 2D)
		myX = (float)x / (float)screenWidth * 2 - 1;
		myY = -((float)y / (float)screenHeight * 2 - 1);

		g_points.push_back(myX);
		g_points.push_back(myY);
		g_points.push_back(0);

		g_colors.push_back(rand() / (float)RAND_MAX);
		g_colors.push_back(rand() / (float)RAND_MAX);
		g_colors.push_back(rand() / (float)RAND_MAX);

		glBindVertexArray(VertexArrayID[0]);
		
		GLuint posLoc = glGetAttribLocation(programID, "inPos");
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID[0]);
		// VBO(Vertex Buffer Object) 
		// arr
		glBufferData(GL_ARRAY_BUFFER, g_points.size() * sizeof(float),
			g_points.data(), GL_STATIC_DRAW);
		// glVertexAttribPointer : 의미부여하는 부분 
		// position -> VBO
		// 3 앞에 3개 읽는다.
		// GL_FLOAT : float 형식 
		// 0 : 한번에 읽는 자리수 
		// (void*)(0) :읽는 첫 자리수 
		glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
		// 쓰겠다고 선언
		glEnableVertexAttribArray(posLoc);

		GLuint colLoc = glGetAttribLocation(programID, "inCol");
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID[1]);
		glBufferData(GL_ARRAY_BUFFER, g_colors.size() * sizeof(float),
			g_colors.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
		glEnableVertexAttribArray(colLoc);
		//glVertexAttrib3f(posLoc, myX, myY, 0.0);

		glBindVertexArray(VertexArrayID[1]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID[0]);
		glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
		glEnableVertexAttribArray(colLoc);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID[1]);
		glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
		glEnableVertexAttribArray(posLoc);

		glutPostRedisplay();
	}
}

void renderScene(void)
{
	//Clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);
	//Let's draw something here

	//define the size of point and draw a point.
	if (g_points.size() > 0)
	{
		// GLuint posLoc = glGetAttribLocation(programID, "inPos");
		// glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID[0]);
		// glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
		// GLuint colLoc = glGetAttribLocation(programID, "inCol");
		// glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID[1]);
		// glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));
		// 다 만든 VBO를 glBindVertexArray 하면 VAO가 된다.  
		glBindVertexArray(VertexArrayID[1]);
		glDrawArrays(GL_LINES, 0, g_points.size() / 3);
		glDrawArrays(GL_POINTS, 0, g_points.size() / 3);
		// glDrawArrays(GL_TRIANGLES, 0, g_points.size() / 3);
	}
	//Double buffer
	glutSwapBuffers();
}


void init()
{
	//initilize the glew and check the errors.
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s' \n", glewGetErrorString(res));
	}

	//select the background color
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	glGenBuffers(2, vertexBufferID);
}


int main(int argc, char** argv)
{
	//init GLUT and create Window
	//initialize the GLUT
	glutInit(&argc, argv);
	//GLUT_DOUBLE enables double buffering (drawing to a background buffer while the other buffer is displayed)
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	//These two functions are used to define the position and size of the window. 
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(screenWidth, screenHeight);
	//This is used to define the name of the window.
	glutCreateWindow("Simple OpenGL Window");

	glutMouseFunc(myMouseFn);

	//call initization function
	init();

	// 1.
	// Generate VAO
	// VAO(Vetex Array Object)
	glGenVertexArrays(2, VertexArrayID);
	glBindVertexArray(VertexArrayID[0]);

	//3. 
	programID = LoadShaders("VertexShader.txt", "FragmentShader.txt");
	glUseProgram(programID);

	glutDisplayFunc(renderScene);

	//enter GLUT event processing cycle
	glutMainLoop();

	glDeleteVertexArrays(2, VertexArrayID);

	return 1;
}