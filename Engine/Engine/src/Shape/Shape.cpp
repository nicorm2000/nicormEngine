#include "Shape.h"

void Shape::SetColor(Vec3 newColor)
{
	colorVector = newColor;
}

Vec3 Shape::GetColor()
{
	return colorVector;
}

void Shape::CreateSquare()
{
    float positions[] = 
    {

            //POSITIONS                 //COLORS
        -0.5f,  -0.5f,   0.0f,      1.0f, 1.0f, 1.0f,
         0.5f,  -0.5f,   0.0f,      1.0f, 1.0f, 1.0f,
         0.5f,   0.5f,   0.0f,      1.0f, 1.0f, 1.0f,
        -0.5f,   0.5f,   0.0f,      1.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    //AGREGAR CREATEBUFFER
    //AGREGAR BINDBUFFER
    //AGREGAR ENABLEATTRIBUTES
    //LO MISMO QUE ARRIBA
}

void Shape::CreateTriangle()
{
    float positions[] = 
    {

        //POSITIONS                 //COLORS
    -0.5f,  -0.5f,   0.0f,      1.0f, 1.0f, 1.0f,
     0.5f,  -0.5f,   0.0f,      1.0f, 1.0f, 1.0f,
     0.5f,   0.5f,   0.0f,      1.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
    };

    //AGREGAR CREATEBUFFER
    //AGREGAR BINDBUFFER
    //AGREGAR ENABLEATTRIBUTES
    //LO MISMO QUE ARRIBA
}

void Shape::Draw()
{
    //AGREGAR DRAWWITHINDEXBUFFER
}