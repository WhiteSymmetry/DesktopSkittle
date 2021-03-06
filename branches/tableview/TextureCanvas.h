#ifndef TXCANVAS
#define TXCANVAS

#include <vector>
#include <iostream>
#include <GL/glut.h>
#include "BasicTypes.h"

using namespace std;

class textureTile{
public:
	int width;
	int height;
	GLuint tex_id;
	vector< unsigned char > data;
	textureTile(int w, int h)
	{
		width = w;
		height = h;
	}
};


class TextureCanvas{
public:
	
	TextureCanvas();
	TextureCanvas(vector<color> pixels, int width);
	~TextureCanvas();
	void display();
	
private:
	void createEmptyTiles(int canvas_width, int canvas_height, int max_size);
	void drawTextureSquare();	
	point2D grid_position(int i, int width, int height, int max_size );
	GLuint loadTexture(textureTile& tile);
	
	GLuint displayList;
	int width;
	int height;
	vector< vector< textureTile > > canvas;
};
#endif
