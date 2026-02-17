#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


int main()
{

	glfwInit();

	glfwWindowHintString(GLFW_CONTEXT_VERSION_MAJOR, "3"); //wersja OpenGL
	glfwWindowHintString(GLFW_CONTEXT_VERSION_MINOR, "4"); //wersja OpenGL
	glfwWindowHintString(GLFW_OPENGL_PROFILE, "core"); //Pakiet funkcji OpenGL

	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, //lewy dolny rog
		 0.5f, -0.5f, 0.0f, //prawy dolny rog
		 0.0f,  0.5f, 0.0f  //srodkowy gorny rog
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


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //utworzenie shadera wierzcholkowego
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //przypisanie kodu shadera
	glCompileShader(vertexShader); //kompilacja shadera

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //utworzenie shadera fragmentowego
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); //przypisanie kodu shadera
	glCompileShader(fragmentShader); //kompilacja shadera

	GLuint shaderProgram = glCreateProgram(); //utworzenie programu shaderowego
	glAttachShader(shaderProgram, vertexShader); //przypisanie shadera wierzcholkowego do programu
	glAttachShader(shaderProgram, fragmentShader); //przypisanie shadera fragmentowego do programu
	glLinkProgram(shaderProgram); //linkowanie programu shaderowego

	glDeleteShader(vertexShader); //usuwanie shadera wierzcholkowego (nie jest juz potrzebny)
	glDeleteShader(fragmentShader); //usuwanie shadera fragmentowego (nie jest juz potrzebny)

	GLuint VBO, VAO; //VBO - Vertex Buffer Object, VAO - Vertex Array Object

	glGenVertexArrays(1, &VAO); //generowanie tablicy wierzcholkow
	glGenBuffers(1, &VBO); //generowanie bufora wierzcholkow

	glBindVertexArray(VAO); //ustawienie tablicy wierzcholkow jako aktywnej
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //ustawienie bufora jako aktywnego

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //przypisanie danych do bufora
	//GL_ARRAY_BUFFER - typ bufora (wierzcholki)
	//sizeof(vertices) - rozmiar danych w bajtach
	//vertices - wskaźnik do danych
	//GL_STATIC_DRAW - sposób użycia danych (statyczne dane, które będą rzadko modyfikowane)
	//można użyć GL_DYNAMIC_DRAW, jeśli dane będą często modyfikowane
	//GL_STREAM_DRAW, jeśli dane będą modyfikowane co klatkę
	//GL_DYNAMIC_DRAW - dane będą często modyfikowane

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //ustawienie atrybutu wierzcholka
	//0 - indeks atrybutu wierzcholka (zgodny z layout(location = 0) w shaderze)
	//3 - liczba komponentów atrybutu (x, y, z)
	//GL_FLOAT - typ danych atrybutu
	//GL_FALSE - normalizacja danych (nie jest potrzebna, ponieważ dane są już w formacie float)
	//3 * sizeof(float) - rozmiar pojedynczego wierzcholka (w bajtach)
	//(void*)0 - offset do danych (w tym przypadku dane zaczynają się od początku bufora)

	glEnableVertexAttribArray(0); //włączenie atrybutu wierzcholka

	glBindBuffer(GL_ARRAY_BUFFER, 0); //odwiązanie bufora
	glBindVertexArray(0); //odwiązanie tablicy wierzcholkow

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram); //użycie programu shaderowego
		glBindVertexArray(VAO); 

		glDrawArrays(GL_TRIANGLES, 0, 3); //rysowanie trójkąta
		//GL_TRIANGLES - tryb rysowania (trójkąty)
		//0 - indeks pierwszego wierzcholka
		//3 - liczba wierzcholkow do narysowania
		
		
		
		
		glfwSwapBuffers(window);
		glfwPollEvents(); //sprawdzanie zdarzen (np. klawiatura, myszka, itp.)
	}

	glDeleteVertexArrays(1, &VAO); //usuwanie tablicy wierzcholkow
	glDeleteBuffers(1, &VBO); //usuwanie bufora wierzcholkow
	glDeleteProgram(shaderProgram); //usuwanie programu shaderowego


	glfwDestroyWindow(window); //niszczenie okna
	glfwTerminate(); //zamykanie biblioteki GLFW
	return 0;
}