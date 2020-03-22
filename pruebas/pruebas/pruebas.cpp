// pruebas.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <math.h>
#include <vector>
#include <array>
#include "Vector2.h"
//Screen dimension constants
int SCREEN_WIDTH = 720;
int SCREEN_HEIGHT = 480;
int tam = 30;
//Starts up SDL and creates window
bool init();
//Frees media and shuts down SDL
void close();
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;
bool init() {
	//Initialization flag
	bool success = true;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);


			}
		}
	}
	return success;
}
void close() {
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;
	SDL_Quit();
}
void SetScreen() {
	if (SCREEN_WIDTH == 0 || SCREEN_HEIGHT == 0) {
		SCREEN_WIDTH = 720;
		SCREEN_HEIGHT = 480;
	}
	if (tam == 0) {
		tam = 32;
	}
}

void Bresenham(float Xa, float Ya, float Xb, float Yb) {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	float x = Xa, y = Ya;
	float dx, dy;
	float p, i;
	int signx;
	int signy;
	dx = Xb - Xa;
	dy = Yb - Ya;
	if (dx >= 0) {
		signx = 1;
	}
	else {
		signx = -1;
	}
	if (dy >= 0) {
		signy = 1;
	}
	else {
		signy = -1;
	}
	if (std::abs(dy) <= std::abs(dx)) {
		p = 2 * dy * signy - dx * signx;
		for (int j = 0; j <= dx * signx; j++) {
			if (p < 0) {
				x = x + signx;
				y = y;
				p = p + 2 * dy * signy;
			}
			else if (p >= 0) {
				x = x + signx;
				y = y + signy;
				p = p + (2 * dy * signy) - (2 * dx * signx);
			}
			SDL_RenderDrawPoint(gRenderer, x, y);
		}
	}
	else if (std::abs(dy) > std::abs(dx)) {
		p = 2 * dx * signx - dy * signy;
		for (int j = 0; j <= dy * signy; j++) {
			if (p < 0) {
				x = x;
				y = y + signy;
				p = p + 2 * dx * signx;
			}
			else if (p >= 0) {
				x = x + signx;
				y = y + signy;
				p = p + (2 * dx * signx) - (2 * dy * signy);
			}
			SDL_RenderDrawPoint(gRenderer, x, y);
		}
	}
	SDL_SetRenderDrawColor(gRenderer, 0xaa, 0xaa, 0xaa, 0xaa);
}
void circunferencia(float R, float Xc, float Yc) {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	float p, x = 0, y = R;
	p = 1 - R;
	for (int i = 0; x <= y; i++) {
		if (p <= 0) {
			x = x + 1;
			y = y;
			p = p + 2 * x + 3;
		}
		else {
			x = x + 1;
			y = y - 1;
			p = p + 2 * x - 2 * y + 5;
		}
		SDL_RenderDrawPoint(gRenderer, x + Xc, y + Yc);
		SDL_RenderDrawPoint(gRenderer, -x + Xc, y + Yc);
		SDL_RenderDrawPoint(gRenderer, -x + Xc, -y + Yc);
		SDL_RenderDrawPoint(gRenderer, x + Xc, -y + Yc);
		SDL_RenderDrawPoint(gRenderer, y + Xc, x + Yc);
		SDL_RenderDrawPoint(gRenderer, -y + Xc, x + Yc);
		SDL_RenderDrawPoint(gRenderer, -y + Xc, -x + Yc);
		SDL_RenderDrawPoint(gRenderer, y + Xc, -x + Yc);
	}
	SDL_SetRenderDrawColor(gRenderer, 0xaa, 0xaa, 0xaa, 0xaa);
}
void DrawPoly(std::vector<Vector2*>& vertex) {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	for (int i = 0; i < vertex.size(); i++) {
		if (i < vertex.size() - 1) {
			Bresenham(vertex[i]->getx(), vertex[i]->gety(), vertex[i + 1]->getx(), vertex[i + 1]->gety());
		}
		else if (i == vertex.size() - 1) {
			Bresenham(vertex[i]->getx(), vertex[i]->gety(), vertex[0]->getx(), vertex[0]->gety());
		}
	}
	SDL_SetRenderDrawColor(gRenderer, 0xaa, 0xaa, 0xaa, 0xaa);
}
int Perriodico(int n, int k) {
	int nuevon = 1;
	int nuevok = 1;
	int nuevaresta = 1;
	int resta = n - k;
	int periodicaFinal;
	if (n == 1) {
		nuevon = 1;
	}
	else {
		for (int i = 1; i <= n; i++) {
			nuevon *= i;
		}
	}
	if (k <= 1) {
		nuevok = 1;
	}
	else {
		for (int i = 1; i <= k; i++) {
			nuevok *= i;
		}
	}
	if (resta <= 1) {
		nuevaresta = 1;
	}
	else {
		for (int i = 1; i <= resta; i++) {
			nuevaresta *= i;
		}
	}
	periodicaFinal = nuevon / (nuevok * nuevaresta);
	return periodicaFinal;
}
void BezierConLineas(std::vector<Vector2*>& vertex) {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	float x, y;
	float xf, yf;
	std::vector<Vector2*>vectorBezier;
	int n = vertex.size() - 1;
	for (float t = 0; t <= 1; t += 0.2) {
		int l = n;
		float sumaDeBezierX = 0;
		float sumaDeBezierY = 0;
		for (float i = 0; i < vertex.size(); i++) {
			float xActual = vertex[i]->getx();
			float yActual = vertex[i]->gety();
			float tConPotencia = std::pow(t, n - l);
			float potenciaDeTMenosUno = std::pow(1 - t, n - i);
			float perriodicoSeparado = Perriodico(n, n - l);
			sumaDeBezierX += (perriodicoSeparado * tConPotencia) * potenciaDeTMenosUno * xActual;
			sumaDeBezierY += (perriodicoSeparado * tConPotencia) * potenciaDeTMenosUno * yActual;
			l -= 1;
		}
		vectorBezier.push_back(new Vector2(sumaDeBezierX, sumaDeBezierY));
		SDL_RenderDrawPoint(gRenderer, sumaDeBezierX, sumaDeBezierY);
	}
	for (int i = 0; i < vectorBezier.size() - 1; i++) {
		Bresenham(vectorBezier[i]->getx(), vectorBezier[i]->gety(), vectorBezier[i + 1]->getx(), vectorBezier[i + 1]->gety());
	}
	SDL_SetRenderDrawColor(gRenderer, 0xaa, 0xaa, 0xaa, 0xaa);
}
void DrawCaja() {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	int  y1 = 0;
	int  y2 = 0;
	for (int i = 0; i < 7; i++) {
		Bresenham(0, y1, 50, y2);
		Bresenham(50, 0, 50, y2);
		y1 += 30;
		y2 += 30; 
	}
	SDL_SetRenderDrawColor(gRenderer, 0xaa, 0xaa, 0xaa, 0xaa);
}
bool linea = false;
bool cuadrado = false;
bool punto = false;
bool sirculo = false;
bool bezier = false;
/*
*@brief aquie se dibuja las lineas, cuadrados, etc
*@param ver es un vector que guerda los puntos que se usaran en la funcion para dibujar
*@return regresa 1 para que se pueda dibujar el punto
*@pos intente varias formas de reemplazar los bool universales (arrays, vectorexs, regresar un valor en especifivo) 
*pero no funcionaron. necesito que los bools sean universales porque necesito 
*que no cambien su valor cada vez que llamo la funion y como ya dije no encontre una forma biable de
*mandar los bools desde el main.
*/
int hola(std::vector<Vector2*>& ver) {
	SDL_Event e;
	int xPrincipal = 0, yPrincipal = 0;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			xPrincipal = e.button.x;
			yPrincipal = e.button.y;
			if (linea == true || cuadrado == true || punto == true 
				|| sirculo == true || bezier == true) {
				ver.push_back(new Vector2(e.button.x, e.button.y));
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN && xPrincipal >= 0 && xPrincipal <= 50 && yPrincipal > 0 && yPrincipal <= 30) {
			punto = true;
			return 1;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN && punto == true) {
			Bresenham(e.button.x, e.button.y, e.button.x, e.button.y);
			punto = false;
			ver.clear();
		}
		if (e.type == SDL_MOUSEBUTTONDOWN && xPrincipal >= 0 && xPrincipal <= 50 && yPrincipal > 30 && yPrincipal <= 60 ) {
			linea = true;
			return 1;
		}
		if (ver.size() > 1 && linea == true) {
			Bresenham(ver.back()->getx(), ver.back()->gety(),
				ver.at(ver.size() - 2)->getx(), ver.at(ver.size() - 2)->gety());
			ver.clear();
			linea = false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN && xPrincipal >= 0 && xPrincipal <= 50 && yPrincipal > 60 && yPrincipal <= 90 ) {
			cuadrado = true;
			return 1;
		}
		if (ver.size() >= 4 && cuadrado == true) {
			DrawPoly(ver);
			ver.clear();
			cuadrado = false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN && xPrincipal >= 0 && xPrincipal <= 50 && yPrincipal > 90 && yPrincipal <= 120) {
			sirculo = true;
			return 1;
		}
		if (ver.size() > 1 && sirculo == true)
		{
			ver.back()->getx(), ver.back()->gety(),
				ver.at(ver.size() - 2)->getx(), ver.at(ver.size() - 2)->gety();
			int dx = ver.back()->getx() - ver.at(ver.size() - 2)->getx();
			int dy = ver.back()->gety() - ver.at(ver.size() - 2)->gety();
			int r = sqrt(pow(dx, 2) + pow(dy, 2));
			circunferencia(r, ver.back()->getx(), ver.back()->gety());
			ver.clear();
			sirculo = false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN && xPrincipal >= 0 && xPrincipal <= 50 && yPrincipal > 120 && yPrincipal <= 150) {
			bezier = true;
			return 1;
		}
		if (bezier == true && e.type == SDL_KEYDOWN) {
			BezierConLineas(ver);
			ver.clear();
			bezier = false;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN && xPrincipal >= 0 && xPrincipal <= 50 && yPrincipal > 150 && yPrincipal <= 180) {
			SDL_RenderClear(gRenderer);
			return 1;
		}
	}
}

int main(int argc, char* args[])
{
	
	/*# dibujo
	hay 6 cuadros en la izquierda de la pantalla

	caja 1 es el boton para dibujar un solo punto
	-para dibujar un solo punto primero aga clic en la primera caja (caja  numero 1 contando de arriba hacia abajo)
	-despues aga clic en cualquier parte de la pantalla que no sea el boton para dibujar un punto

	caja 2 es el boton para dibujar una linea
	-para dibujar una linea primero aga clic en la segunda caja (caja numero 2 contando de arriba hacia abajo)
	-despues haga clic en dos lugares diferentes de la pantalla (la linea se dibujara despues del segundo clic)

	caja 3 es el boton para dibujar un cuadrado
	-para dibujar un cuadrado primero aga clic en la tercera caja (caja numero 3 contando de arriba hacia abajo)
	-despues haga clic en 4 partes diferentes de la pantalla (el cuadrado se dibujara despues del cuarto clic)

	caja 4 es el boton para dibujar un circulo
	-para dibujar un circulo primero aga clic en la cuarta caja (caja numero 4 contando de arriba hacia abajo)
	-despues aga clic en dos puntos diferentes de la pantalla, el segundo clic es el centro del sirculo y
	y tambien sirve para calcular la distancia entre el primer clic y el segundo clic esto nos da el radio,
	(despues del segundo clic se dibujara el circulo)

	caja 5 es el boton para dibujar una linea de Bezier
	-para dibujar una linea de Bezier primero aga clic en la quinta caja (caja numero 5 contando de arriba hacia abajo)
	-despues haga cuantos clics quiera en la pantalla (preferiblemente simetricos) cuando quiera que se dibuje la linea
	oprima cualquier tecla despues de hacer los clics que quiera.

	 caja 6 es el boton para borrar todo
	-si oprime el boton borrara todos los dibujos*/
	SetScreen();
	std::vector<Vector2*>ver;
	bool linea = false;
	bool cuadrado = false;
	bool punto = false;
	bool sirculo = false;
	bool bezier = false;
	//int precionado = 0;
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		//Main loop flag
		bool quit = false;
		//Event handler
		SDL_Event e;
		int n = 0;
		//While application is running
		while (!quit) {
			//precionado += hola(precionado);
			hola(ver);
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0) {
				//User requests quit
				if (e.type == SDL_QUIT) {
					quit = true;
				}
			}
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			std::vector<Vector2*>vertex;
			SDL_RenderDrawPoint(gRenderer, 0, 0);
			DrawCaja();
			SDL_SetRenderDrawColor(gRenderer, 0xaa, 0xaa, 0xaa, 0xaa);
			SDL_RenderPresent(gRenderer);
		}
	}
	return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
