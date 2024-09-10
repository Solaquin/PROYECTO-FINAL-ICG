/* CLASE LA CUAL MANEJA EL FLUJO Y MOVIMIENTO DE LAS VENTANAS Y
*  LO QUE SE PRESENTA EN ELLA. */

#pragma once
#include <iostream>
#include "Graficos.h"
#include <math.h>
#include <vector>

struct Button //STRUCT QUE ALMACENA LA INFORMACIÓN CUANDO SE CONSTRUYE UN BOTON
{
	int px, py, anchoBttn, altoBttn, id;
	std::string text;
};

struct Pregunta //Struct que almacena y determina el manejo de las preguntas
{
	std::string pregunta;
	std::vector<Button> opciones;
	int seleccionada;
	GLuint imageTextura;
};

class DisplayHandler
{
public:
	DisplayHandler();
	DisplayHandler(int ancho, int alto);
	~DisplayHandler();

	void crearBoton(Button boton, Color bttnText, Color bttnColor);//Función para crear y gráficar botones
	void motionCallback(int px, int py);//Función que reconoce movimiento del mouse
	void clickCallback(int state, int click, int cx, int cy);

	void iniciarBotonesMenu();
	void iniciarBotonesInformacion();
	void iniciarBotonesResultados();
	void mostrarBotonesMenu();
	void mostrarBotonesInformacion();
	void mostrarBotonesResultados();

	static void textoInformacion();
	int getActualDisplay();
	Button getClickedButton(int px, int py, std::vector<Button> bttnList);//Retorna el botón que haya dentro de los parametros establecidos en una lista de botones
	void initPreguntas();
	void initTablaDeDatos();
	void mostrarPregunta(Pregunta _pregunta);//Grafica caracteristicas de las preguntas
	void mostrarPreguntaActual();//Muestra la pregunta actual
	int getIndexPregunta(); 
	void mostrarResultados();
	int getRespuestasCorrectas(Pregunta _preguntas[],const int _respuestas[]);//Compara y cuenta el numero de respuestas correctas 

private:
	int ancho, alto;
	std::vector <Button> listaBttnsInicio, listaBttnsInfo, listaBttnsResultados;
	int actualDisplay, indexPregunta;
	Pregunta preguntas[12];
	const int respuestas[12] = { 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };//Lista que contiene los indices de las respuestas correctas de cada pregunta
	GLuint* texturas;//Lista que guarda las texturas que se cargan
	Celda tablaDeDatos[13][3];
};

