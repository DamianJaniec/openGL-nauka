#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Mesh.h"

void init();

GLFWwindow* window;



GLfloat verticesBasic[] = {
		-0.5f,  -0.5f, 0.0f,//lewy dolny rog
		 0.5f,  -0.5f, 0.0f,//prawy dolny rog
		 0.0f,   0.5f, 0.0f,//srodkowy gorny rog
		-0.5f / 2, 0.0f, 0.0f,
		 0.5f / 2, 0.0f, 0.0f,
		 0.0f,  -0.5f, 0.0f
};

GLfloat vertices[] = {
		-0.5f,  -0.5f, 0.0f,	1.0f, 1.0f, 1.0f,//lewy dolny rog
		 0.5f,  -0.5f, 0.0f,	1.0f, 1.0f, 0.0f,//prawy dolny rog
		 0.0f,   0.5f, 0.0f,	1.0f, 0.0f, 0.0f, //srodkowy gorny rog
		-0.5f / 2, 0.0f, 0.0f,	0.0f, 1.0f, 1.0f,
		 0.5f / 2, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		 0.0f,  -0.5f, 0.0f,    0.0f, 0.0f, 0.0f

};

GLuint indices[] = {
	0, 3, 5, //pierwszy trójkąt
	3, 2, 4, //drugi trójkąt
	5, 4, 1  //trzeci trójkąt
};


int main()
{
	init();

	Shader shaderProgramDef(ShaderType::DEFAULT);

	Mesh triangle(vertices, indices, sizeof(vertices), sizeof(indices),shaderProgramDef.type);
	triangle.setScale(0.5f);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgramDef.Activate();

		triangle.Draw(shaderProgramDef);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window); 
		glfwPollEvents();
	}

	triangle.Delete();
	shaderProgramDef.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void init()
{
	glfwInit();

	glfwWindowHintString(GLFW_CONTEXT_VERSION_MAJOR, "3"); //wersja OpenGL
	glfwWindowHintString(GLFW_CONTEXT_VERSION_MINOR, "4"); //wersja OpenGL
	glfwWindowHintString(GLFW_OPENGL_PROFILE, "core"); //Pakiet funkcji OpenGL

	window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	//szerokosc, wysokosc, tytul, monitor (NULL - okno nie jest pelnoekranowe), share (NULL - brak wspolnego kontekstu)

	if (window == NULL)
	{
		std::cout << "Nie udalo sie utworzyc okna :(" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window); //ustawienie "kontekstu" dla okna

	gladLoadGL(); //zaladowanie funkcji OpenGL

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //ustawienie koloru tła (r, g, b, a)


	glClear(GL_COLOR_BUFFER_BIT); //wyczyszczenie bufora koloru
	glfwSwapBuffers(window); //zamiana buforów (double buffering)

	glViewport(0, 0, 800, 800); //ustawienie rozmiaru okna (x, y, szerokosc, wysokosc)

}