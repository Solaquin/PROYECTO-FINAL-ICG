/* CLASE LA CUAL CONTIENE PRIMITIVAS GRAFICAS Y METODOS NECESARIOS
*  PARA GRAFICAR Y MOSTRAR OBJETOS EN LA VENTANA. */

#pragma once
#include <iostream>
#include <GL/glut.h>
#include <math.h>
#include <vector>
#include <string>

struct Color
{
	float r, g, b;
};

struct Coords //ALMACENA INFORMACIÓN DE LAS COORDENADAS
{
	int x, y;
};

struct Celda
{
	std::string texto;
	int tipo;
	Color color;
};

class Graficar
{
public:
	Graficar();
	~Graficar();
	static void texto(std::string texto, int px, int py, Color color);
	static void pixel(float px, float py, float r, float g, float b);
	static void trazarFigura(std::vector<Coords> listaVertices, Color lineColor); //Traza figura dependiendo de una lista de vertices
	static void trazarFigura(int px, int py, int width, int height, Color lineColor); //Traza una figura segun posicion x, y, ancho y alto
	static void rellenarFigura(std::vector<Coords> listaVertices, Color colorRelleno, short tipo); //Tipo: 0 - Solido, 1 - Degradado
	static void graficarLinea(int x1, int x2, int y1, int y2, Color lineColor);
	static int obtenerAnchoTexto(const std::string texto);
	static void dibujarCeldas(int x, int y, int ancho, int alto, std::string texto); //Dibuja celdas sin color
	static void dibujarCeldas(int x, int y, int ancho, int alto, std::string texto, Color color); //Dibuja celdas con un color de fondo
	static void dibujarTabla(Celda datosTabla[][3]);
	static void dibujarImagen(int textura, float x, float y, float width, float height);
	static GLuint cargarTextura(const char* archivo, int& width, int& height); //Carga texturas desde archivos
	void initTexturas(); //Inicializa las texturas determinadas
	GLuint* getTexturas(); //Retorna la lista de texturas

private:
	GLuint texturasIshihara[12];
	GLuint texturaInicio;
};