#include "Render.h"
#include <fstream>
#include <iostream>
#include <sstream>

Render::Render(Window* window)
{
	this->shader = nullptr;
	view = glm::mat4(0.f);
	projection = glm::mat4(0.f);

	yaw = -90.f;
	pitch = 0.f;
	sensitivity = 0.5f;
	fov = 100;

	this->window = window;

	// CAMERA POSITION
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // Camera position -> vector un world space that point's to the camera's position
	cameraP = cameraPos;
	// CAMERA DIRECTION
	// For the view matrix, we want z-axis to be positive, so because (in OpenGL) the 
	// camera points towards the negative z-axis, we want to negate the direction vector
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // vector of in what direction it is pointing at
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); // position vector - origin vector = camera's direction vector    

	// RIGHT AXIS
	// This represents the positive x-axis of the camera space. First we use an up vector
	// that points upwards in world space, and then we do a cross product on the up vector
	// and the direction vector. The result is a vector perpendicular to both vectors,
	// getting a vector that points in the positive x-axis's direction.
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraF = cameraFront;
	// UP AXIS
	// We take the cross product of the right and direction vector and we get the vector
	// that points to the camera's positive y-axis.
	glm::vec3 cameraUpLocal = glm::cross(cameraDirection, cameraRight);
	cameraUp = cameraUpLocal;
	// LOOK AT MATRIX
	// Creates a view matrix that looks at a given target (position, direction, up).

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	projection = glm::perspective(glm::radians(fov), (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 2000.0f);
}

Render::~Render()
{
	if (window != nullptr)
	{
		window = nullptr;
		delete window;
	}

	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}
}

void Render::UpdateProjection()
{
	projection = glm::perspective(glm::radians(GetFOV()), (float)window->GetWidth() / (float)window->GetHeight(), 0.1f, 2000.0f);
}

//Borrar porque no va
void Render::UpdateCameraPos(glm::vec3 pos)
{
	glm::vec3 cameraPos = glm::vec3(pos);
	cameraP = cameraPos;

	view = glm::lookAt(cameraPos, cameraPos + cameraF, cameraUp);
}

void Render::UpdateDirection()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	SetFront(glm::normalize(direction));

	view = glm::lookAt(cameraP, cameraP + cameraF, cameraUp);
}

void Render::SetFront(glm::vec3 front)
{
	this->cameraF = front;
}

glm::vec3 Render::GetFront()
{
	return cameraF;
}

void Render::SetUp(glm::vec3 up)
{
	this->cameraUp = up;
}

glm::vec3 Render::GetUp()
{
	return cameraUp;
}

void Render::SetYaw(float yaw)
{
	this->yaw = yaw;
}

void Render::SetPitch(float pitch)
{
	this->pitch = pitch;
}

void Render::SetSensitivity(float sensitivity)
{
	this->sensitivity = sensitivity;
}

float Render::GetSensitivity()
{
	return sensitivity;
}
float Render::GetYaw()
{
	return yaw;
}

float Render::GetPitch()
{
	return pitch;
}

void Render::SetFOV(float fov)
{
	this->fov = fov;
	UpdateProjection();
}

float Render::GetFOV()
{
	return fov;
}

void Render::SetView(glm::mat4 view)
{
	this->view = view;
}

void Render::SetProjection(glm::mat4 projection)
{
	this->projection = projection;
}

void Render::SetDepth()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Render::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Render::ClearScreenWithColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	glClearColor(r, g, b, a);
	ClearScreen();
}

void Render::SwapBuffers(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

int Render::InitGLEW()
{
	if (glewInit() != GLEW_OK) return -1;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Render::InitShader()
{
	//shader = new Shader();
	//shader->CreateShader("../src/shaders/vertex.shader", "../src/shaders/fragment.shader");
}

void Render::InitMaterial()
{
	//PUEDE TENER PROBLEMAS
	material = new Material();
	ShaderProgramSource source = material->ParseShader("shaders/Textures.shader");
	material->CreateMaterial(source.VertexSource, source.FragmentSource);
	material->UseMaterial();
}

void Render::CreateBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Render::BindBuffers(GLsizeiptr sizeVertices, GLsizeiptr sizeIndices, const GLvoid* vertices, const GLvoid* indices, unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glBindVertexArray(VAO);

	// Vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeVertices, vertices, GL_STATIC_DRAW);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndices, indices, GL_STATIC_DRAW);
}

void Render::UnBindVertex(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Render::EnableVertexAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* offset)
{
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	glEnableVertexAttribArray(index);
}

void Render::BindTexture(GLenum target, GLuint texture)
{
	glBindTexture(target, texture);
}

void Render::DrawWithoutIndexBuffer(GLenum primitive, GLint offset, GLsizei count)
{
	glDrawArrays(primitive, offset, count);
}

void Render::DrawWithIndexBuffer(GLenum primitive, GLsizei count, GLenum type, const GLvoid* indices, unsigned int& VAO)
{
	glBindVertexArray(VAO);

	glDrawElements(primitive, count, type, indices);
	glBindVertexArray(0);
}

glm::mat4 Render::GetViewMatrix()
{
	return view;
}

glm::mat4 Render::GetProjectionMatrix()
{
	return projection;
}

Material* Render::GetMaterial()
{
	return material;
}





void Render::UseShader()
{
	glUseProgram(GetShaderId());
}

unsigned int Render::GetShaderId()
{
	return shader->GetShaderId();
}

void Render::CleanShader()
{
	glUseProgram(0);
}

void Render::GenBuffers(unsigned int& VAO, unsigned int& VBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void Render::GenBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Render::GenBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int& UVB)
{
	GenBuffers(VAO, VBO, EBO);
	glGenBuffers(1, &UVB);
}

void Render::BindBuffer(unsigned int VAO, unsigned int VBO, int tam, const void* vertices)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
}

void Render::BindIndexs(unsigned int EBO, int tam, unsigned int* indexs)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tam, indexs, GL_STATIC_DRAW);
}

void Render::BindUV(unsigned int UVB, int tam, float* vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, UVB);
	glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_DYNAMIC_DRAW);
}

void Render::UnBind(unsigned int& VAO, unsigned int& VBO)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Render::UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Render::UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int& UVB)
{
	UnBind(VAO, VBO, EBO);
	glDeleteBuffers(1, &UVB);
}

void Render::SetLocation(unsigned int& location, const char* loc)
{
	location = glGetAttribLocation(GetShaderId(), loc);
}

void Render::SetUniform(unsigned int& uniform, const char* loc)
{
	uniform = glGetUniformLocation(GetShaderId(), loc);
}

void Render::SetBaseAttribs(unsigned int location, int size, GLsizei stride, const void* offset)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, offset);
}

void Render::SetTextureAttribs(unsigned int location, int size, int stride, int offset)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)offset);
}

void Render::UpdateMVP(unsigned int uniformModel, unsigned int uniformView, unsigned int uniformProjection, glm::mat4 model)
{
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
}

void Render::UpdateVec3(unsigned int uniformVec3, glm::vec3 vec3Value)
{
	glUniform3f(uniformVec3, vec3Value.x, vec3Value.y, vec3Value.z);
}

void Render::UpdateColor(unsigned int uniformBaseColor, unsigned int uniformAlpha, glm::vec4 baseColor)
{
	glUniform3fv(uniformBaseColor, 1, glm::value_ptr(glm::vec3(baseColor.r, baseColor.g, baseColor.b)));
	glUniform1fv(uniformAlpha, 1, &(baseColor.a));
}

void Render::UpdateStatus(unsigned int uniformStatus, bool status)
{
	glUniform1i(uniformStatus, status);
}

void Render::UpdateLight(unsigned int uniformLight, glm::vec3 light)
{
	glUniform3fv(uniformLight, 1, glm::value_ptr(light));
}

void Render::UpdateTexture(unsigned int uniformTexture, unsigned int textureId)
{
	glUniform1f(uniformTexture, (GLfloat)textureId);
}

void Render::UpdateFloatValue(unsigned int uniformFloat, float value)
{
	glUniform1f(uniformFloat, value);
}

void Render::UpdateIntValue(unsigned int uniformInt, int value)
{
	glUniform1i(uniformInt, value);
}

void Render::UpdateCameraView(unsigned int uniformView, glm::vec3 position)
{
	glUniform3f(uniformView, position.x, position.y, position.z);
}

void Render::UpdateLightVec3(unsigned int uniformLightVec3, glm::vec3 light)
{
	glUniform3f(uniformLightVec3, light.x, light.y, light.z);
}

void Render::UpdateLightFloat(unsigned int uniformLightFloat, float value)
{
	glUniform1f(uniformLightFloat, value);
}

void Render::UpdateLightStatus(unsigned int uniformLightStatus, bool status)
{
	glUniform1i(uniformLightStatus, status);
}

unsigned int Render::GetUniform(unsigned int shaderId, const char* loc)
{
	return glGetUniformLocation(shaderId, loc);
}

void Render::Draw(unsigned int VAO, unsigned int vertices)
{
	glBindVertexArray(VAO);

	if (vertices == 3) glDrawArrays(GL_TRIANGLES, 0, vertices);
	else glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Render::DrawLines(unsigned int VAO, unsigned int vertices)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, vertices);
	glBindVertexArray(0);
}

void Render::BindDiffuseMap(unsigned int textureId)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Render::BindSpecularMap(unsigned int textureId)
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Render::TextureEnable()
{
	glEnable(GL_TEXTURE_2D);
}

void Render::TextureDisable()
{
	glDisable(GL_TEXTURE_2D);
}

void Render::TextureDelete(unsigned int uniformTexture, unsigned int& textureId)
{
	glDeleteTextures(uniformTexture, &textureId);
}

void Render::BlendEnable()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Render::BlendDisable()
{
	glDisable(GL_BLEND);
}

void Render::UseTexture(int number, unsigned int id)
{
	glActiveTexture(GL_TEXTURE0 + number);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Render::CleanTexture()
{
	glActiveTexture(GL_TEXTURE0);
}