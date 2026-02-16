#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main()
{

	glfwInit();

	glfwWindowHintString(GLFW_CONTEXT_VERSION_MAJOR, "3"); //wersja OpenGL
	glfwWindowHintString(GLFW_CONTEXT_VERSION_MINOR, "4"); //wersja OpenGL
	glfwWindowHintString(GLFW_OPENGL_PROFILE, "core"); //Pakiet funkcji OpenGL

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

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents(); //sprawdzanie zdarzen (np. klawiatura, myszka, itp.)
	}




	glfwDestroyWindow(window); //niszczenie okna
	glfwTerminate(); //zamykanie biblioteki GLFW
	return 0;
}