#include "MyTexture.h"
#include "GLEW/glew.h"
#include <iostream>

//MyTexture::MyTexture(const std::string path,bool flip)
//{
//	std::cout << "-----Create new Texture-----"<<std::endl;
//	_id = 0;
//	_width = 0;
//	_height = 0;
//	_bitDepth = 0;
//	_channels = 0;
//	_path = path;
//	if (TextureImporter::LoadTexture(_path, _id, _width, _height, _channels, flip))
//	{
//		std::cout << "Texture load suscefully" << std::endl;
//	}
//	else
//	{
//		std::cout << "Texture load FAIL" << std::endl;
//	}
//	std::cout << "-----End Create new Texture----" << std::endl;
//}
//MyTexture::MyTexture()
//{
//	_id = 0;
//	_width = 0;
//	_height = 0;
//	_bitDepth = 0;
//	_channels = 0;
//	_path = "";
//}
//MyTexture::~MyTexture() {
//	glDeleteTextures(1, &_id);
//	_id = 0;
//	_width = 0;
//	_height = 0;
//	_bitDepth = 0;
//	_path = " ";
//}
//
//bool MyTexture::LoadTexture(const std::string path, bool flip) {
//	_path = path;
//	return TextureImporter::LoadTexture(_path, _id, _width, _height, _channels, flip);
//}
//void MyTexture::UseTexture() {
//	glEnable(GL_TEXTURE_2D);
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, _id);
//}
//void MyTexture::StopTexture() {
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glDisable(GL_TEXTURE_2D);
//}