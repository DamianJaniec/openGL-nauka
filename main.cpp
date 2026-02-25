#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "shaderProgram.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Mesh.h"
#include "Texture.h"

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

GLfloat verticesBox[] = {
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // lewy dolny
	-0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 1.0f,  // lewy górny
	 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 1.0f,  // prawy górny 
	 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f   // prawy dolny 
};

GLuint indices[] = {
	0, 3, 5, //pierwszy trójkąt
	3, 2, 4, //drugi trójkąt
	5, 4, 1  //trzeci trójkąt
};

GLuint indicesBox[] = {
	0, 1, 2, //pierwszy trójkąt
	0, 3, 2  //drugi trójkąt
};

int main()
{
	init();

	Shader shaderProgramTex(ShaderType::TEXTURE);
	Mesh square(verticesBox, indicesBox, sizeof(verticesBox), sizeof(indicesBox),shaderProgramTex.type);
	square.setScale(0.5f);

	Texture texture("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); //utworzenie tekstury na podstawie danych z pliku
	square.setTexture(&texture);

	
	Shader shaderProgramDef(ShaderType::DEFAULT);
	Mesh triangle(vertices, indices, sizeof(vertices), sizeof(indices), shaderProgramDef.type);
	triangle.setScale(0.5f);

	Shader shaderProgramBasic(ShaderType::BASIC);
	Mesh triangleBasic(verticesBasic, indices, sizeof(verticesBasic), sizeof(indices), shaderProgramBasic.type);
	

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgramTex.Activate();
		square.Draw(shaderProgramTex);

		shaderProgramDef.Activate();
		triangle.Draw(shaderProgramDef);

		shaderProgramBasic.Activate();
		triangleBasic.Draw(shaderProgramBasic);
		

		glfwSwapBuffers(window); 
		glfwPollEvents();
	}

	square.Delete();
	texture.Delete();
	shaderProgramTex.Delete();

	triangle.Delete();
	shaderProgramDef.Delete();

	triangleBasic.Delete();
	shaderProgramBasic.Delete();

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