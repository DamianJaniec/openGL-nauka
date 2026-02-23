#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

int main()
{

	glfwInit();

	glfwWindowHintString(GLFW_CONTEXT_VERSION_MAJOR, "3"); //wersja OpenGL
	glfwWindowHintString(GLFW_CONTEXT_VERSION_MINOR, "4"); //wersja OpenGL
	glfwWindowHintString(GLFW_OPENGL_PROFILE, "core"); //Pakiet funkcji OpenGL

	GLfloat vertices[] = {
		-0.5f,  -0.5f, 0.0f,	0.8f, 0.3f,  0.02f,//lewy dolny rog
		 0.5f,  -0.5f, 0.0f,	0.8f, 0.3f,  0.02f,//prawy dolny rog
		 0.0f,   0.5f, 0.0f,	1.0f, 0.6f,  0.32f,//srodkowy gorny rog
		-0.5f/2, 0.0f, 0.0f,	0.9f, 0.45f, 0.17f,
		 0.5f/2, 0.0f, 0.0f,	0.9f, 0.45f, 0.17f,
		 0.0f,  -0.5f, 0.0f,	0.8f, 0.3f,  0.02f  

	};

	GLuint indices[] = {
		0, 3, 5, //pierwszy trójkąt
		3, 2, 4, //drugi trójkąt
		5, 4, 1  //trzeci trójkąt
	};
	

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	//szerokosc, wysokosc, tytul, monitor (NULL - okno nie jest pelnoekranowe), share (NULL - brak wspolnego kontekstu)

	if (window == NULL) 
	{
		std::cout << "Nie udalo sie utworzyc okna :(" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window); //ustawienie "kontekstu" dla okna

	gladLoadGL(); //zaladowanie funkcji OpenGL

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //ustawienie koloru tła (r, g, b, a)
	glClear(GL_COLOR_BUFFER_BIT); //wyczyszczenie bufora koloru
	glfwSwapBuffers(window); //zamiana buforów (double buffering)

	glViewport(0, 0, 800, 800); //ustawienie rozmiaru okna (x, y, szerokosc, wysokosc)

	Shader shaderProgram("default.vert", "default.frag"); //utworzenie programu shaderowego na podstawie plików z kodem shadera

	VAO VAO1; //utworzenie obiektu VAO
	VAO1.Bind(); //wiązanie obiektu VAO (ustawienie jako aktywnego

	VBO VBO1(vertices, sizeof(vertices)); //utworzenie bufora wierzcholkow na podstawie danych
	EBO EBO1(indices, sizeof(indices)); //utworzenie bufora indeksow na podstawie danych

	VAO1.linkAttrib(VBO1, 0,3,GL_FLOAT,6*sizeof(float), (void*)0); //przypisanie bufora wierzcholkow do obiektu VAO
	VAO1.linkAttrib(VBO1, 1,3,GL_FLOAT,6*sizeof(float), (void*)(3*sizeof(float))); //przypisanie bufora wierzcholkow do obiektu VAO
	VAO1.Unbind(); //odwiązanie obiektu VAO (ustawienie jako nieaktywnego)
	VBO1.Unbind(); //odwiązanie bufora wierzcholkow (ustawienie jako nieaktywnego
	EBO1.Unbind(); //odwiązanie bufora indeksow (ustawienie jako nieaktywnego
	

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); //pobranie ID uniformu "scale" z programu shaderowego

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate(); //użycie programu shaderowego
		glUniform1f(uniID, -0.5f); //ustawienie wartości uniformu "scale"
		VAO1.Bind(); //wiązanie obiektu VAO (ustawienie jako aktywnego)
		EBO1.Bind(); //wiązanie bufora indeksow (ustawienie jako aktywnego)
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0); //rysowanie trójkątów na podstawie indeksów (tryb rysowania, liczba indeksów, typ danych indeksów, offset)

		
		
		glfwSwapBuffers(window);
		glfwPollEvents(); //sprawdzanie zdarzen (np. klawiatura, myszka, itp.)
	}

	VAO1.Delete(); //usunięcie obiektu VAO
	VBO1.Delete(); //usunięcie bufora wierzcholkow
	EBO1.Delete(); //usunięcie bufora indeksow
	shaderProgram.Delete(); //usunięcie programu shaderowego

	glfwDestroyWindow(window); //niszczenie okna
	glfwTerminate(); //zamykanie biblioteki GLFW
	return 0;
}