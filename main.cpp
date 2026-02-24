#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Texture.h"
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
		//   pozycja			//kolor				//tekstura
		-0.5f,  -0.5f, 0.0f,	1.0f, 0.0f,  0.0f,	0.0f, 0.0f,
		-0.5f,   0.5f, 0.0f,	0.0f, 1.0f,  0.0f,	0.0f, 1.0f,
		 0.5f,   0.5f, 0.0f,	0.0f, 0.0f,  1.0f,	1.0f, 1.0f,
		 0.5f,  -0.5f, 0.0f,	1.0f, 1.0f,  1.0f,	1.0f, 0.0f
	};

	GLuint indices[] = {
		0, 2, 1,
		0, 3, 2
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

	VAO1.linkAttrib(VBO1, 0,3,GL_FLOAT,8*sizeof(float), (void*)0); //przypisanie bufora wierzcholkow do obiektu VAO
	VAO1.linkAttrib(VBO1, 1,3,GL_FLOAT,8*sizeof(float), (void*)(3*sizeof(float))); //przypisanie bufora wierzcholkow do obiektu VAO
	VAO1.linkAttrib(VBO1, 2,2,GL_FLOAT,8*sizeof(float), (void*)(6*sizeof(float))); //przypisanie bufora wierzcholkow do obiektu VAO
	VAO1.Unbind(); //odwiązanie obiektu VAO (ustawienie jako nieaktywnego)
	VBO1.Unbind(); //odwiązanie bufora wierzcholkow (ustawienie jako nieaktywnego
	EBO1.Unbind(); //odwiązanie bufora indeksow (ustawienie jako nieaktywnego
	

	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale"); //pobranie ID uniformu "scale" z programu shaderowego

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); //ustawienie flagi do odwracania obrazu w pionie podczas ładowania (przydatne, ponieważ OpenGL ma inny układ współrzędnych tekstur niż większość formatów obrazów)
	unsigned char* data = stbi_load("pop_cat.png", &width, &height, &nrChannels, 0); //zaladowanie obrazu z pliku (sciezka, szerokosc, wysokosc, liczba kanalow, wymuszona liczba kanalow)
	if (!data) std::cout << "Nie udalo sie zaladowac tekstury!" << std::endl;


/*	GLuint texture;
	glGenTextures(1, &texture); //generowanie tekstury
	glActiveTexture(GL_TEXTURE0); //aktywacja jednostki tekstur (GL_TEXTURE0 - GL_TEXTURE31)
	glBindTexture(GL_TEXTURE_2D, texture); //wiązanie tekstury (ustawienie jako aktywnej)

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//float flatColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //ustawienie danych tekstury (cel, poziom szczegolow, format wewnetrzny, szerokosc, wysokosc, border, format danych, typ danych, dane
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //ustawienie danych tekstury (cel, poziom szczegolow, format wewnetrzny, szerokosc, wysokosc, border, format danych, typ danych, dane
	glGenerateMipmap(GL_TEXTURE_2D); //generowanie mipmap dla tekstury


	stbi_image_free(data); //zwolnienie pamieci zajmowanej przez dane obrazu
	glBindTexture(GL_TEXTURE_2D, 0); //odwiązanie tekstury (ustawienie jako nieaktywnej)

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "tex0"); //pobranie ID uniformu "tex0" z programu shaderowego
	shaderProgram.Activate(); //użycie programu shaderowego
	glUniform1i(tex0Uni, 0); //ustawienie wartości uniformu "tex0" (indeks jednostki tekstur)*/

	Texture texture("pop_cat.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE); //utworzenie tekstury na podstawie danych z pliku
	texture.texUnit(shaderProgram, "tex0", 0); //przypisanie jednostki tekstur do uniformu w programie shaderowym

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate(); //użycie programu shaderowego
		glUniform1f(uniID, 0.5f); //ustawienie wartości uniformu "scale"
		//glBindTexture(GL_TEXTURE_2D, texture);
		texture.Bind(); //wiązanie tekstury (ustawienie jako aktywnej)
		VAO1.Bind(); //wiązanie obiektu VAO (ustawienie jako aktywnego)
		EBO1.Bind(); //wiązanie bufora indeksow (ustawienie jako aktywnego)
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie trójkątów na podstawie indeksów (tryb rysowania, liczba indeksów, typ danych indeksów, offset)

		
		
		glfwSwapBuffers(window);
		glfwPollEvents(); //sprawdzanie zdarzen (np. klawiatura, myszka, itp.)
	}

	VAO1.Delete(); //usunięcie obiektu VAO
	VBO1.Delete(); //usunięcie bufora wierzcholkow
	EBO1.Delete(); //usunięcie bufora indeksow
	shaderProgram.Delete(); //usunięcie programu shaderowego
	//glDeleteTextures(1, &texture); //usunięcie tekstury
	texture.Delete(); //usunięcie tekstury

	glfwDestroyWindow(window); //niszczenie okna
	glfwTerminate(); //zamykanie biblioteki GLFW
	return 0;
}