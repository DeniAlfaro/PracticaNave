// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

//Declarar una ventana
GLFWwindow* window;

float posXTriangulo = 0.0f, posYTriangulo = 0.0f;
double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.5;
float angulo = 0.0f;

void teclado_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_RIGHT) {
		posXTriangulo += 0.01;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_LEFT) {
		posXTriangulo -= 0.01;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_UP) {
		posYTriangulo += 0.01;
	}
	if ((action == GLFW_PRESS || action == GLFW_REPEAT) && key == GLFW_KEY_DOWN) {
		posYTriangulo -= 0.01;
	}
}

float compX;
float compY; 
void actualizar() {
	//posXTriangulo += 0.00001;

	tiempoActual = glfwGetTime();
	double tiempoDiferencial = tiempoActual - tiempoAnterior;
	float velocidadAngular = 40.0f;

	int estadoDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoDerecha == GLFW_PRESS) {
		angulo -= velocidadAngular * tiempoDiferencial;
	}
	int estadoIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoIzquierda == GLFW_PRESS) {
		angulo += velocidadAngular * tiempoDiferencial;
	}
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		compX = (cos((angulo + 90.0) * 3.14159 / 180.0)) * (velocidadTriangulo * tiempoDiferencial);
		compY = (sin((angulo + 90.0) * 3.14159 / 180.0)) * (velocidadTriangulo * tiempoDiferencial);

		posXTriangulo += compX;
		posYTriangulo += compY;

		//Que salga de la pantalla y vuelva aparecer
		if (posXTriangulo <= -1.08) {
			posXTriangulo = 1.00;
		}
		else if (posXTriangulo >= 1.08) {
			posXTriangulo = -1.00;
		}

		if (posYTriangulo <= -1.08) {
			posYTriangulo = 1.00;
		}
		else if (posYTriangulo >= 1.08) {
			posYTriangulo = -1.00;
		}
	}
	/*int estadoAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoAbajo == GLFW_PRESS) {
		posYTriangulo -= velocidadTriangulo * tiempoDiferencial;
	}*/
	tiempoAnterior = tiempoActual;
}

void dibujar() {
	glPushMatrix();

	glTranslatef(posXTriangulo, posYTriangulo, 0.0f);
	glRotatef(angulo, 0.0f, 0.0f, 1.0f);
	glScalef(0.4f, 0.7f, 0.7f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.2, 0.6, 0.1);
	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);

	glEnd();

	glPopMatrix();
}

int main()
{

	//Si no se pudo iniciar GLFW terminamos ejecucion
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW, inicializamos la ventana
	window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL);
	//Si no se pudo crear la ventana, terminamos la ejecucion
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos la ventana como contexto
	glfwMakeContextCurrent(window);

	//Una vez establecido el contexto se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//Establecemos que con cada evento de teclado se llama a la funcion teclado_callback
	//glfwSetKeyCallback(window, teclado_callback);

	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;

	//Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window))
	{
		//Establecer region de dibujo
		glViewport(0, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(3, 0.8, 0.4, 1);
		//Borrar
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Actualizar valores y dibujar
		actualizar();
		dibujar();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	//Despues del ciclo de dibujo, eliminamos ventana y procesos de glfw
	glfwDestroyWindow(window);
	glfwTerminate();
}