#include "Graficos.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>


Graficar::Graficar()
{

}

Graficar::~Graficar()
{

}

void Graficar::texto(std::string texto, int px, int py, Color txtColor)
{
    glColor3f(txtColor.r, txtColor.g, txtColor.b);
    glRasterPos2f(px, py);
    for (char c : texto)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void Graficar::pixel(float px, float py, float r, float g, float b)
{
	glPointSize(5);
	glColor3f(r, g, b);
	glBegin(GL_POINTS);
	glVertex2f(px, py);
	glEnd();
}

void Graficar::trazarFigura(std::vector<Coords> listaVertices, Color lineColor)
{
	int i;

	for (i = 0; i < listaVertices.size() - 1; i++)
	{
		graficarLinea(listaVertices[i].x, listaVertices[i + 1].x, listaVertices[i].y, listaVertices[i + 1].y, lineColor);
	}

	// Conectar el último vértice con el primer vértice para cerrar la figura
	graficarLinea(listaVertices[i].x, listaVertices[0].x, listaVertices[i].y, listaVertices[0].y, lineColor);
}

void Graficar::trazarFigura(int px, int py, int width, int height, Color lineColor)
{
	std::vector<Coords> listAux;
	listAux.push_back(Coords{ px , py });
	listAux.push_back(Coords{ px + width, py });
	listAux.push_back(Coords{ px + width, py - height });
	listAux.push_back(Coords{ px, py - height });

	int i;

	for (i = 0; i < listAux.size() - 1; i++)
	{
		graficarLinea(listAux[i].x, listAux[i + 1].x, listAux[i].y, listAux[i + 1].y, lineColor);
	}

	// Conectar el último vértice con el primer vértice para cerrar la figura
	graficarLinea(listAux[i].x, listAux[0].x, listAux[i].y, listAux[0].y, lineColor);
}

void Graficar::rellenarFigura(std::vector<Coords> _puntos, Color colorRelleno, short tipo)
{
	float r = colorRelleno.r;
	float g = colorRelleno.g;
	float b = colorRelleno.b;

	if (_puntos.size() < 3) {
		return;  // Se requieren al menos 3 vértices para formar un polígono
	}

	int minY = _puntos[0].y;
	int maxY = _puntos[0].y;

	for (int i = 0; i < _puntos.size(); i++)
	{
		if (_puntos[i].y < minY) {
			minY = _puntos[i].y;
		}
		if (_puntos[i].y > maxY) {
			maxY = _puntos[i].y;
		}
	}

	// Itera sobre cada línea horizontal escaneando el polígono
	for (int y = minY; y <= maxY; y++)
	{
		std::vector<int> intersecciones;

		for (int i = 0; i < _puntos.size(); i++)
		{
			int j = (i + 1) % _puntos.size();
			Coords p1 = _puntos[i];
			Coords p2 = _puntos[j];

			if ((p1.y <= y && p2.y > y) || (p2.y <= y && p1.y > y)) {
				// Calcula la intersección de la línea horizontal con el lado del polígono
				int x = p1.x + (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
				intersecciones.push_back(x);
			}
		}

		// Ordena las intersecciones manualmente en orden ascendente
		for (int i = 0; i < intersecciones.size() + 1; i++)
		{
			for (int j = i + 1; j < intersecciones.size(); j++)
			{
				if (intersecciones[i] > intersecciones[j])
				{
					int temp = intersecciones[i];
					intersecciones[i] = intersecciones[j];
					intersecciones[j] = temp;
				}
			}
		}

		if (tipo == 1)
		{
			if (r == 1)
			{
				g += 0.005;
				b += 0.005;
			}
			else if (g == 1)
			{
				r += 0.005;
				b += 0.005;
			}
			else if (b == 1)
			{
				r += 0.005;
				g += 0.005;
			}
			else
			{
				r += 0.005;
				g += 0.005;
				b += 0.005;
			}

		}

		// Dibuja los píxeles entre las intersecciones
		for (int i = 0; i < intersecciones.size(); i += 2)
		{
			int x1 = intersecciones[i];
			int x2 = intersecciones[i + 1];

			for (int x = x1; x <= x2; x++)
			{
				pixel(x, y, r, g, b);  // Rellena el píxel
			}
		}
	}
}

void Graficar::graficarLinea(int x1, int x2, int y1, int y2, Color lineColor)
{
	float r = lineColor.r;
	float g = lineColor.g;
	float b = lineColor.b;

	int paramInicial, aux, paramNuevo, x, y;
	int dx = x2 - x1;
	int dy = y2 - y1;

	const float m = (float)dy / (float)dx; //Calculo de pendiente
	//Calcular incremento dependiendo de la pendiente
	int incrementoY = (m < 0) ? -1 : 1;
	int incrementoX = (m < 0) ? -1 : 1;
	float mAbs = abs(m);

	if (1 > mAbs)
	{
		if (x2 < x1)  //Cambiar puntos en caso de que el punto inicial se coloque en una posición mayor a la del final
		{
			aux = x1;
			x1 = x2;
			x2 = aux;
			aux = y1;
			y1 = y2;
			y2 = aux;
			dx = abs(dx);
		}
		dy = abs(dy);
		x = x1, y = y1;

		paramInicial = (2 * dy) - dx;
		paramNuevo = paramInicial;
		while (x <= x2)
		{
			if (paramNuevo <= 0)
			{
				paramNuevo += 2 * dy;
			}
			else
			{
				paramNuevo += 2 * (dy - dx);
				y += incrementoY;
			}

			pixel(x, y, r, g, b);
			x++;
		}
	}
	else //Mismos calculos que en el if anterior, pero esta vez se realizan con respecto al eje y, para poder graficar en los octantes 2, 3, 6 y 7
	{
		if (y2 < y1) //Cambiar puntos en caso de que el punto inicial se coloque en una posición mayor a la del final
		{
			aux = x1;
			x1 = x2;
			x2 = aux;
			aux = y1;
			y1 = y2;
			y2 = aux;
			dy = abs(dy);
		}
		dx = abs(dx);
		x = x1, y = y1;

		paramInicial = (2 * dx) - dy;
		paramNuevo = paramInicial;
		while (y <= y2)
		{
			if (paramNuevo <= 0)
			{
				paramNuevo += 2 * dx;
			}
			else
			{
				paramNuevo += 2 * (dx - dy);
				x += incrementoX;
			}

			pixel(x, y, r, g, b);
			y++;
		}
	}
}

int Graficar::obtenerAnchoTexto(const std::string texto) 
{
	int ancho = 0;
	for (char c : texto) 
	{
		ancho += glutBitmapWidth(GLUT_BITMAP_HELVETICA_18, c);
	}

	return ancho;
}

void Graficar::dibujarCeldas(int x, int y, int ancho, int alto, std::string txt)
{
	std::vector<Coords> listAux;
	listAux.push_back(Coords{ x , y });
	listAux.push_back(Coords{ x + ancho, y });
	listAux.push_back(Coords{ x + ancho, y - alto });
	listAux.push_back(Coords{ x, y - alto });

	trazarFigura(listAux, { 1,1,1 });

	float textX = x + (ancho - obtenerAnchoTexto(txt)) * 0.5;
	float textY = y - alto * 0.7;
	texto(txt, textX, textY, { 1,1,1 });

}

void Graficar::dibujarCeldas(int x, int y, int ancho, int alto, std::string txt, Color color)
{
	std::vector<Coords> listAux;
	listAux.push_back(Coords{ x , y });
	listAux.push_back(Coords{ x + ancho, y });
	listAux.push_back(Coords{ x + ancho, y - alto });
	listAux.push_back(Coords{ x, y - alto });

	rellenarFigura(listAux, color, 0);
	trazarFigura(listAux, { 1,1,1 });

	float textX = x + (ancho - obtenerAnchoTexto(txt)) * 0.5;
	float textY = y - alto * 0.7;
	texto(txt, textX, textY, { 0,0,0 });
}

void Graficar::dibujarTabla(Celda datosTabla[][3])
{
	int anchoTabla = 940, altoTabla = 600;
	int filas = 13;
	int columnas = 3;
	float anchoCelda = anchoTabla/columnas, altoCelda = 35;

	// Dibuja cada celda en la tabla
	for (int fila = 0; fila < filas; ++fila) {
		for (int columna = 0; columna < columnas; ++columna) {
			float x = -470 + columna * anchoCelda;
			float y = 280 - fila * altoCelda;
			const Celda& celda = datosTabla[fila][columna];
			if (celda.tipo == 0)
			{
				dibujarCeldas(x, y, anchoCelda, altoCelda, celda.texto);
			}
			else
			{
				dibujarCeldas(x, y, anchoCelda, altoCelda, celda.texto, celda.color);
			}

		}
	}
}


void Graficar::dibujarImagen(int textura, float x, float y, float width, float height)
{
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textura);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(x, y);                // Esquina inferior izquierda
	glTexCoord2f(1.0, 1.0);
	glVertex2f(x + width, y);       // Esquina inferior derecha
	glTexCoord2f(1.0, 0.0);
	glVertex2f(x + width, y + height);  // Esquina superior derecha
	glTexCoord2f(0.0, 0.0);
	glVertex2f(x, y + height);       // Esquina superior izquierda
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

GLuint Graficar::cargarTextura(const char* archivo, int& width, int& height)
{
	unsigned char* data = stbi_load(archivo, &width, &height, nullptr, 4);

	if (!data) {
		std::cout << "Error al cargar la imagen: " << archivo << std::endl;
		exit(1);
	}

	GLuint textura;
	glGenTextures(1, &textura);
	glBindTexture(GL_TEXTURE_2D, textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);  // Libera la memoria utilizada por la imagen

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return textura;
}

void Graficar::initTexturas()
{
	int w, h;

	//CARGAR TEXTURAS DE IMAGENES DE ISHIHARA
	texturasIshihara[0] = cargarTextura("IMAGENES/1.png", w, h);
	texturasIshihara[1] = cargarTextura("IMAGENES/2.png", w, h);
	texturasIshihara[2] = cargarTextura("IMAGENES/3.png", w, h);
	texturasIshihara[3] = cargarTextura("IMAGENES/4.png", w, h);
	texturasIshihara[4] = cargarTextura("IMAGENES/5.png", w, h);
	texturasIshihara[5] = cargarTextura("IMAGENES/6.png", w, h);
	texturasIshihara[6] = cargarTextura("IMAGENES/7.png", w, h);
	texturasIshihara[7] = cargarTextura("IMAGENES/8.png", w, h);
	texturasIshihara[8] = cargarTextura("IMAGENES/9.png", w, h);
	texturasIshihara[9] = cargarTextura("IMAGENES/10.png", w, h);
	texturasIshihara[10] = cargarTextura("IMAGENES/11.png", w, h);
	texturasIshihara[11] = cargarTextura("IMAGENES/12.png", w, h);
}

GLuint* Graficar::getTexturas()
{
	return texturasIshihara;
}
