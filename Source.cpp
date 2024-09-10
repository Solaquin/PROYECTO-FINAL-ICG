#include "Graficos.h"
#include "displayHandler.h"

#define ANCHO 1080
#define ALTO 720

int initVentana(int, int, const char*, void());
int initSubVentana(int, int, int, void());
void display();
void passiveMotionMouse(int, int);
void clickMouseFunc(int, int, int, int);

DisplayHandler disHand = DisplayHandler(ANCHO, ALTO);

int window, selectedDisplay = disHand.getActualDisplay();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	window = initVentana(ANCHO, ALTO, "PROYECTO ICG", display);

	//Funciones para activar el canal alpha y visualizar correctamente imagenes png
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glutPassiveMotionFunc(passiveMotionMouse);
	glutMouseFunc(clickMouseFunc);

	glutMainLoop();

	return 0;
}

int initVentana(int ancho, int alto, const char* name, void funcDis())
{
	int id;
	glutInitWindowSize(ancho, alto);
	glutInitWindowPosition(1280 / 2, 1020 / 6);
	id = glutCreateWindow(name);
	gluOrtho2D(-ANCHO / 2, ANCHO / 2, -ALTO / 2, ALTO / 2);
	glutDisplayFunc(funcDis);
	return id;
}

int initSubVentana(int ancho, int alto, int win, void funcDis())
{
	int id;
	id = glutCreateSubWindow(win, ancho/2, alto/2, 400, 400);
	gluOrtho2D(-ANCHO / 2, ANCHO / 2, -ALTO / 2, ALTO / 2);
	glutDisplayFunc(funcDis);
	return id;
}

void display()
{
	glClearColor(56.0/255.0, 58.0/255.0, 64.0/255.0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	disHand.iniciarBotonesMenu();
	disHand.iniciarBotonesInformacion();
	disHand.iniciarBotonesResultados();

	if (selectedDisplay == 0) //Inicio del test
	{
		Graficar::trazarFigura(-370, 320, 750, 640, { 0.0,1.0,0.0 });
		std::string texto = "TEST DE ISHIHARA";
		int textWidth = Graficar::obtenerAnchoTexto(texto);
		Graficar::texto(texto, -textWidth / 2, 250, { 1,1,1 });
		int indexPregunta = disHand.getIndexPregunta();
		if (indexPregunta <= 11)
		{
			disHand.mostrarPreguntaActual();
		}
	}
	else if (selectedDisplay == 1) //Información del test
	{
		Graficar::trazarFigura(-370, 175, 750, 315, { 1,0,0 });
		std::string texto = "INFORMACION";
		int textWidth = Graficar::obtenerAnchoTexto(texto);
		Graficar::texto(texto, -textWidth / 2, 250, { 1,1,1 });
		DisplayHandler::textoInformacion();
		disHand.mostrarBotonesInformacion();
	}
	else if (selectedDisplay == 2) //Resultados del test
	{
		int w, h;
		GLuint textura = Graficar::cargarTextura("IMAGENES/bob.png", w, h);
		Graficar::dibujarImagen(textura, 80, 280, 15, 20);

		std::string texto = "RESULTADOS";
		int textWidth = Graficar::obtenerAnchoTexto(texto);
		Graficar::texto(texto, -textWidth / 2, 300, { 1,1,1 });
		disHand.initTablaDeDatos();
		disHand.mostrarResultados();
		disHand.mostrarBotonesResultados();
	}
	else //Pantalla principal 
	{
		int w, h;
		GLuint textura = Graficar::cargarTextura("IMAGENES/inicio.jpg", w, h);

		Graficar::dibujarImagen(textura, -ANCHO / 2, -ALTO / 2, 1080, 720);

		std::string texto = "PRUEBA DE DALTONISMO";
		int textWidth = Graficar::obtenerAnchoTexto(texto);
		Graficar::texto(texto, -textWidth / 2, 200, { 1,1,1 });

		disHand.mostrarBotonesMenu();
	}
	glFlush();
}

void passiveMotionMouse(int x, int y)
{
	disHand.motionCallback(x - (ANCHO / 2), (ALTO / 2) - y);
}

void clickMouseFunc(int state, int click, int cx, int cy)
{
	disHand.clickCallback(state, click, cx, cy);
	selectedDisplay = disHand.getActualDisplay();
	glutPostRedisplay();
}