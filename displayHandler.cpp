#include "displayHandler.h"


DisplayHandler::DisplayHandler()
{
    ancho = 800;
    alto = 600;
}

DisplayHandler::DisplayHandler(int _ancho, int _alto)
{
    ancho = _ancho;
    alto = _alto;
    actualDisplay = -1;
    indexPregunta = 0;
}

DisplayHandler::~DisplayHandler()
{
    actualDisplay = -1;
}

void DisplayHandler::crearBoton(Button boton, Color bttnColor, Color txtColor)
{
    Button aux;
    std::vector<Coords> listAux;

    listAux.push_back(Coords{ boton.px, boton.py });
    listAux.push_back(Coords{ boton.px + boton.anchoBttn, boton.py });
    listAux.push_back(Coords{ boton.px + boton.anchoBttn, boton.py - boton.altoBttn });
    listAux.push_back(Coords{ boton.px, boton.py - boton.altoBttn });
    Graficar::trazarFigura(listAux, bttnColor);
    Graficar::rellenarFigura(listAux, bttnColor, 1);

    // Dibuja el texto en el boton
    int textWidth = Graficar::obtenerAnchoTexto(boton.text); // Sustituye con la función correcta para medir el ancho del texto

    int textX = boton.px + (boton.anchoBttn - textWidth) / 2;
    int textY = (boton.py - boton.altoBttn / 1.7);

    // Dibuja el texto centrado en el botón
    Graficar::texto(boton.text, textX, textY, txtColor);
    listAux.clear();

}

void DisplayHandler::motionCallback(int px, int py)
{
    bool isInButton = false;

    if (actualDisplay == -1)
    {
        for (const Button& button : listaBttnsInicio)
        {
            if ((px >= button.px && px <= button.px + button.anchoBttn) && (py <= button.py && py >= button.py - button.altoBttn))
            {
                isInButton = true;
                break;
            }
            else
            {
                isInButton = false;
            }
        }
    }
    if (actualDisplay == 1)
    {
        for (const Button& button : listaBttnsInfo)
        {
            if ((px >= button.px && px <= button.px + button.anchoBttn) && (py <= button.py && py >= button.py - button.altoBttn))
            {
                isInButton = true;
                break;
            }
            else
            {
                isInButton = false;
            }
        }
    }
    if (actualDisplay == 0)
    {
        for (const Button& button : preguntas[indexPregunta].opciones)
        {
            if ((px >= button.px && px <= button.px + button.anchoBttn) && (py <= button.py && py >= button.py - button.altoBttn))
            {
                isInButton = true;
                break;
            }
            else
            {
                isInButton = false;
            }
        }
    }
    if (actualDisplay == 2)
    {
        for (const Button& button : listaBttnsResultados)
        {
            if ((px >= button.px && px <= button.px + button.anchoBttn) && (py <= button.py && py >= button.py - button.altoBttn))
            {
                isInButton = true;
                break;
            }
            else
            {
                isInButton = false;
            }
        }
    }

    if (isInButton)
    {
        glutSetCursor(GLUT_CURSOR_CROSSHAIR);

    }
    else
    {
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    }
}

void DisplayHandler::clickCallback(int state, int click, int cx, int cy)
{
    int IDBttnClicked = -1;
    Button bttn;

    if (state == GLUT_DOWN && click == GLUT_LEFT_BUTTON)
    {
        if (actualDisplay == -1) //Determina en que display se encuentra para saber que se debe mostrar en pantalla
        {
            indexPregunta = 0;

            bttn = getClickedButton(cx - (ancho / 2), (alto / 2) - cy, listaBttnsInicio);
            IDBttnClicked = bttn.id;

            if (IDBttnClicked == 0)
            {
                initPreguntas();
                actualDisplay = 0;
            }
            else if (IDBttnClicked == 1)
            {
                actualDisplay = 1;
            }
            else if (IDBttnClicked == 2)
            {
                exit(0);
            }
        }
        else if (actualDisplay == 0)
        {
            int IDBttnClickedPregunta = -1;
            Button bttnPregunta;

            if (indexPregunta <= 11) 
            {
                bttnPregunta = getClickedButton(cx - (ancho / 2), (alto / 2) - cy, preguntas[indexPregunta].opciones);
                IDBttnClickedPregunta = bttnPregunta.id;

                if (IDBttnClickedPregunta != -1)
                {
                    preguntas[indexPregunta].seleccionada = IDBttnClickedPregunta;
                    indexPregunta++;
                }
                IDBttnClickedPregunta = -1;
            }
            if (indexPregunta == 12)
            {
                actualDisplay = 2;
            }
        }
        else if (actualDisplay == 1)
        {
            bttn = getClickedButton(cx - (ancho / 2), (alto / 2) - cy, listaBttnsInfo);
            IDBttnClicked = bttn.id;

            if (IDBttnClicked == 0)
            {
                actualDisplay = -1;
            }
        }
        else if (actualDisplay == 2)
        {
            bttn = getClickedButton(cx - (ancho / 2), (alto / 2) - cy, listaBttnsResultados);
            IDBttnClicked = bttn.id;

            if (IDBttnClicked == 0)
            {
                actualDisplay = -1;
            }
        }
    }

}

void DisplayHandler::iniciarBotonesMenu()
{
    listaBttnsInicio.push_back( { -125, 80, 250, 80, 0, "INICIO"});
    listaBttnsInicio.push_back( { -125, -40, 250, 80, 1, "INFORMACION"});
    listaBttnsInicio.push_back( { -125, -160, 250, 80, 2, "SALIR"});
}

void DisplayHandler::iniciarBotonesInformacion()
{
    listaBttnsInfo.push_back( { (-glutGet(GLUT_INIT_WINDOW_WIDTH) / 2) + 170 , -220, 120, 50, 0, "VOLVER"} );
}

void DisplayHandler::iniciarBotonesResultados()
{
    listaBttnsResultados.push_back({ 270 , -250, 200, 50, 0, "VOLVER A INICIO" });
}

void DisplayHandler::mostrarBotonesMenu()
{
    crearBoton(listaBttnsInicio[0], { 0.129,0.384,0.235 }, { 1,1,1 });
    crearBoton(listaBttnsInicio[1], { 0.129,0.129,0.384 }, { 1,1,1 });
    crearBoton(listaBttnsInicio[2], { 0.384,0.129,0.129 }, { 1,1,1 });
}

void DisplayHandler::mostrarBotonesInformacion()
{
    crearBoton(listaBttnsInfo[0], { 0.384,0.129,0.129 }, { 1,1,1 });
}

void DisplayHandler::mostrarBotonesResultados()
{
    crearBoton(listaBttnsResultados[0], { 0.384,0.129,0.129 }, { 1,1,1 });
}

void DisplayHandler::textoInformacion()
{

    std::string parrafo = { "La prueba de Ishihara, es un examen de percepcion del color\n"
                              "utilizado para evaluar la capacidad de una persona para\n"
                              "distinguir los colores y detectar deficiencias en la visión del\n"
                              "color, especialmente el daltonismo.\n"
                              "En la prueba de Ishihara, se presentaran una serie de figuras con\n" 
                              "puntos de colores en diferentes patrones. El objetivo de la\n" 
                              "persona sometida a la prueba es identificar y leer los números o\n" 
                              "patrones ocultos dentro de los puntos de colores.\n"
                              "Los resultados que se mostraran al final de la prueba se\n"
                              "utilizaran para diagnosticar y clasificar los diferentes tipos de\n"
                              "daltonismo y determinar la gravedad de la deficiencia en la\n"
                              "vision del color."
    };

    std::vector<std::string> lineas;
    int inicio = 0;
    int fin;

    while ((fin = parrafo.find('\n', inicio)) != std::string::npos) //Encuentra un salto de linea o el final del parrafo
    {
        lineas.push_back(parrafo.substr(inicio, fin - inicio));
        inicio = fin + 1; // Avanza después del salto de línea
    }

    // Agrega la última línea (o la única línea si no hay saltos de línea al final)
    lineas.push_back(parrafo.substr(inicio));

    int y = 120;
    for (const std::string line : lineas)
    {
        int textWidth = Graficar::obtenerAnchoTexto(line);
        Graficar::texto(line.c_str(), -textWidth / 2, y, { 1, 1, 1 });
        y -= 20; // Ajusta la posición vertical para la próxima línea
    }

}

int DisplayHandler::getActualDisplay()
{
    return actualDisplay;
}

Button DisplayHandler::getClickedButton(int px, int py, std::vector<Button> listaBttns)
{
    Button aux = Button();

    for (const Button& button : listaBttns)
    {
        //Busca un boton dentro de la lista pasada como parametro, el cual cumpla que el click se haya dado dentro de su rango
        if ((px >= button.px && px <= button.px + button.anchoBttn) && (py <= button.py && py >= button.py - button.altoBttn))
        {
            return button;
        }
    }

    aux.id = -1; //Si el click no fue dado dentro de un botón de la lista retorna un botón con el ID: -1
    return aux;
}

void DisplayHandler::initPreguntas()
{
    //Inicializa cada una de las preguntas que se mostraran manualmente

    Graficar g;
    Pregunta aux;

    g.initTexturas();
    texturas = g.getTexturas();

    //Pregunta 1
    aux.pregunta = "¿Que numero ves? escoge una opcion.";
    aux.opciones = { Button{-125, -200, 100, 80, 0, "12"}, Button{25, -200, 100, 80, 1, "Ninguno"}}; //"12", "Ninguno"
    aux.imageTextura = texturas[0];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[0] = aux;

    //Pregunta 2
    aux.pregunta = "¿Que numero ves? escoge una opcion.";
    aux.opciones = { Button{-225, -200, 100, 80, 0, "5"}, Button{ -50, -200, 100, 80, 1, "6" }, Button{125, -200, 100, 80, 2, "Ninguno"} }; //"5","6", "Ninguno"
    aux.imageTextura = texturas[1];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[1] = aux;

    //Pregunta 3
    aux.pregunta = "¿Que numero ves? escoge una opcion.";
    aux.opciones = { Button{-225, -200, 100, 80, 0, "15"}, Button{ -50, -200, 100, 80, 1, "17" }, Button{125, -200, 100, 80, 2, "Ninguno"} }; //"15","17", "Ninguno"
    aux.imageTextura = texturas[2];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[2] = aux;

    //Pregunta 4
    aux.pregunta = "¿Que numero ves? escoge una opcion.";
    aux.opciones = { Button{-225, -200, 100, 80, 0, "21"}, Button{ -50, -200, 100, 80, 1, "74" }, Button{125, -200, 100, 80, 2, "Ninguno"} }; //"21","74", "Ninguno"
    aux.imageTextura = texturas[3];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[3] = aux;

    //Pregunta 5
    aux.pregunta = "¿Que numero ves? escoge una opcion.";
    aux.opciones = { Button{-125, -200, 100, 80, 0, "2"}, Button{25, -200, 100, 80, 1, "Ninguno"} };
    aux.imageTextura = texturas[4];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[4] = aux;

    //Pregunta 6
    aux.pregunta = "¿Que numero ves? escoge una opcion.";
    aux.opciones = { Button{-125, -200, 100, 80, 0, "97"}, Button{25, -200, 100, 80, 1, "Ninguno"} }; //"2", "Ninguno"
    aux.imageTextura = texturas[5];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[5] = aux;

    //Pregunta 7
    aux.pregunta = "¿Que numero ves? escoge una opcion.";
    aux.opciones = { Button{-125, -200, 100, 80, 0, "73"}, Button{25, -200, 100, 80, 1, "Ninguno"} }; //"73", "Ninguno"
    aux.imageTextura = texturas[6];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[6] = aux;

    //Pregunta 8
    aux.pregunta = "¿Que numero ves? escoge una opcion.";
    aux.opciones = { Button{-225, -200, 100, 80, 0, "57"}, Button{ -50, -200, 100, 80, 1, "35" }, Button{125, -200, 100, 80, 2, "Ninguno"} }; //"57","35", "Ninguno"
    aux.imageTextura = texturas[7];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[7] = aux;

    //Pregunta 9
    aux.pregunta = "¿Que numero ves o que numero distingues de mejor manera? escoge una opcion.";
    aux.opciones = { Button{-275, -200, 100, 80, 0, "26"}, Button{ -125, -200, 100, 80, 1, "6" }, Button{ 25, -200, 100, 80, 2, "2" }, Button{175, -200, 100, 80, 3, "Ninguno"} }; //"26","6","2", "Ninguno"
    aux.imageTextura = texturas[8];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[8] = aux;

    //Pregunta 10
    aux.pregunta = "¿Que numero ves o que numero distingues de mejor manera? escoge una opcion.";
    aux.opciones = { Button{-275, -200, 100, 80, 0, "42"}, Button{ -125, -200, 100, 80, 1, "4" }, Button{ 25, -200, 100, 80, 2, "2" }, Button{175, -200, 100, 80, 3, "Ninguno"} }; //"42", "4", "2", "Ninguno"
    aux.imageTextura = texturas[9];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[9] = aux;

    //Pregunta 11
    aux.pregunta = "¿Que numero ves o que numero distingues de mejor manera? escoge una opcion.";
    aux.opciones = { Button{-275, -200, 100, 80, 0, "35"}, Button{ -125, -200, 100, 80, 1, "3" }, Button{ 25, -200, 100, 80, 2, "5" }, Button{175, -200, 100, 80, 3, "Ninguno"} }; //"35", "3", "5", "Ninguno"
    aux.imageTextura = texturas[10];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[10] = aux;

    //Pregunta 12
    aux.pregunta = "¿Que numero ves o que numero distingues de mejor manera? escoge una opcion.";
    aux.opciones = { Button{-275, -200, 100, 80, 0, "96"}, Button{ -125, -200, 100, 80, 1, "9" }, Button{ 25, -200, 100, 80, 2, "6" }, Button{175, -200, 100, 80, 3, "Ninguno"} }; //"96","9","6", "Ninguno"
    aux.imageTextura = texturas[11];  // Asigna el valor adecuado según tu implementación
    aux.seleccionada = -1;
    preguntas[11] = aux;

}

void DisplayHandler::initTablaDeDatos()
{
    Celda _tablaDeDatos[13][3] = {
        {{"FIGURA", 0},{"TU RESPUESTA",0},{"RESPUESTA CORRECTA", 0}},
        {{"PREGUNTA #1", 0},{},{"12", 0} },
        {{"PREGUNTA #2", 0},{},{"6", 0}},
        {{"PREGUNTA #3", 0},{},{"15", 0}},
        {{"PREGUNTA #4", 0},{},{"74", 0}},
        {{"PREGUNTA #5", 0},{},{"2", 0}},
        {{"PREGUNTA #6", 0},{},{"97", 0}},
        {{"PREGUNTA #7", 0},{},{"73", 0}},
        {{"PREGUNTA #8", 0},{},{"57", 0}},
        {{"PREGUNTA #9", 0},{},{"26", 0}},
        {{"PREGUNTA #10", 0},{},{"42", 0}},
        {{"PREGUNTA #11", 0},{},{"35", 0}},
        {{"PREGUNTA #12", 0},{},{"96", 0}}
    }; //Inicializa los datos constantes de la tabla, los datos que almacena la matriz es del tipo Struct Celda

    for (int i = 0; i < 12; i++)
    {
        if (preguntas[i].seleccionada == respuestas[i]) //Confirma si la respuesta almacenada es igual a las respuestas determinadas, si es correcta la celda se mostrara de color verde
        {
            Color verde = { 0,1,0 };
            std::string seleccionada = preguntas[i].opciones[preguntas[i].seleccionada].text; //Obtiene el texto del boton de opcion de la respuesta elegida

            _tablaDeDatos[i + 1][1] = Celda { seleccionada, 1, verde}; //Almacena en la matriz la celda en la posición de la pregunta
        }
        else //Si la respuesta es incorrecta la celda sera de color rojo
        {
            Color rojo = { 1,0,0 };
            std::string seleccionada = preguntas[i].opciones[preguntas[i].seleccionada].text;

            _tablaDeDatos[i + 1][1] = Celda {seleccionada, 1, rojo };
        }
    }

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tablaDeDatos[i][j] = _tablaDeDatos[i][j]; //Almacena el auxiliar en la tabla de datos miembro de la clase
        }
    }
}

void DisplayHandler::mostrarPregunta(Pregunta _pregunta)
{
    std::string text = "Pregunta #" + std::to_string(indexPregunta + 1);

    Graficar::dibujarImagen(_pregunta.imageTextura, -250 / 2, -80, 250, 250); //Grafica la imagen asociada a la textura antes inicializada
    Graficar::texto(_pregunta.pregunta, -(Graficar::obtenerAnchoTexto(_pregunta.pregunta) / 2), -140, { 1,1,1 }); //Grafica la pregunta almacenada en el objeto actual
    Graficar::texto(text, -(Graficar::obtenerAnchoTexto(text) / 2), 200, {1,1,1}); 

    int numBotones = _pregunta.opciones.size(); //Obtiene el numero de botones de opciones

    for (int i = 0; i < numBotones; i++)
    {
        crearBoton(_pregunta.opciones[i], { 0.255,0.361,0.341 }, { 1,1,1 }); //Crea los botones de la pregunta actual con sus valores iniciados y guardados anteriormente
    }
}

void DisplayHandler::mostrarPreguntaActual()
{
    mostrarPregunta(preguntas[indexPregunta]);
}

int DisplayHandler::getIndexPregunta()
{
    return indexPregunta;
}

void DisplayHandler::mostrarResultados()
{
    float resCorrectas = getRespuestasCorrectas(preguntas, respuestas);
    float porcentaje = ( resCorrectas / 12) * 100; //Calcula el porcentaje de respuestas correctas
    Graficar::dibujarTabla(tablaDeDatos);
    Graficar::texto("RESULTADO DE LA PRUEBA: " + std::to_string((int)round(porcentaje)) + "% (" + std::to_string((int)resCorrectas) + "/12)", -470, -260, {1,1,1});
    Graficar::texto("DIAGNOSTICO: ", -470, -290, { 1,1,1 });
    if (porcentaje >= 0 && porcentaje <= 30)
    {
        Graficar::texto("Severa deficiencia de vision de color.", -320, -290, { 1,1,1 });
    }
    else if (porcentaje > 30 && porcentaje <= 70)
    {
        Graficar::texto("Moderada deficiencia de vision de color.", -320, -290, { 1,1,1 });
    }
    else if (porcentaje > 70 && porcentaje <= 90)
    {
        Graficar::texto("Ligera deficiencia de vision de color.", -320, -290, { 1,1,1 });
    }
    else
    {
        Graficar::texto("Vision del color normal", -320, -290, { 1,1,1 });
    }

}

int DisplayHandler::getRespuestasCorrectas(Pregunta _preguntas[],const int _respuestas[])
{
    float resCorrectas = 0;

    for (int i = 0; i < 12; i++)
    {
        if (_preguntas[i].seleccionada == _respuestas[i])
        {
            resCorrectas++;
        }
    }

    return resCorrectas;
}
