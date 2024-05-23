#include "Renderer.h"

Renderer::Renderer()
{
	this->shader = nullptr;
	clearColor = Color(0.1f, 0.1f, 0.1f, 1.0f);

	view = glm::mat4(0.f);
	projection = glm::mat4(0.f);
}

Renderer::~Renderer()
{
	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}
}

int Renderer::InitGLEW()
{
	// Init GLEW
	if (glewInit() != GLEW_OK) return -1;
}

void Renderer::InitShader()
{
	shader = new Shader();
	shader->CreateShader("../src/shaders/vertex.shader", "../src/shaders/fragment.shader");
}

void Renderer::UseShader()
{
	glUseProgram(GetShaderId());
}

unsigned int Renderer::GetShaderId()
{
	return shader->GetShaderId();
}

void Renderer::CleanShader()
{
	glUseProgram(0);
}

void Renderer::SetDepth()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void Renderer::ClearScreen()
{
	glClearColor(clearColor.GetColorRGBA().r, clearColor.GetColorRGBA().g, clearColor.GetColorRGBA().b, clearColor.GetColorRGBA().a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearScreenWithColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	// Sets the color to clear the screen and clears the context window
	glClearColor(r, g, b, a);
}

void Renderer::SwapBuffers(Window* window)
{
	glfwSwapBuffers(window->GetWindow());
}

void Renderer::GenBuffers(unsigned int& VAO, unsigned int& VBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
}

void Renderer::GenBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
}

void Renderer::GenBuffers(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int& UVB)
{
	GenBuffers(VAO, VBO, EBO);
	glGenBuffers(1, &UVB);
}

void Renderer::BindBuffer(unsigned int VAO, unsigned int VBO, int tam, const void* vertices)
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_STATIC_DRAW);
}

void Renderer::BindIndexs(unsigned int EBO, int tam, unsigned int* indexs)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tam, indexs, GL_STATIC_DRAW);
}

void Renderer::BindUV(unsigned int UVB, int tam, float* vertices)
{
	glBindBuffer(GL_ARRAY_BUFFER, UVB);
	glBufferData(GL_ARRAY_BUFFER, tam, vertices, GL_DYNAMIC_DRAW);
}

void Renderer::UnBind(unsigned int& VAO, unsigned int& VBO)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Renderer::UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Renderer::UnBind(unsigned int& VAO, unsigned int& VBO, unsigned int& EBO, unsigned int& UVB)
{
	UnBind(VAO, VBO, EBO);
	glDeleteBuffers(1, &UVB);
}

void Renderer::SetLocation(unsigned int& location, const char* loc)
{
	location = glGetAttribLocation(GetShaderId(), loc);
}

void Renderer::SetUniform(unsigned int& uniform, const char* loc)
{
	uniform = glGetUniformLocation(GetShaderId(), loc);
}

void Renderer::SetBaseAttribs(unsigned int location, int size, GLsizei stride, const void* offset)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, offset);
}

void Renderer::SetTextureAttribs(unsigned int location, int size, int stride, int offset)
{
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)offset);
}

void Renderer::UpdateMVP(unsigned int uniformModel, unsigned int uniformView, unsigned int uniformProjection, glm::mat4 model)
{
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::UpdateVec3(unsigned int uniformVec3, glm::vec3 vec3Value)
{
	glUniform3f(uniformVec3, vec3Value.x, vec3Value.y, vec3Value.z);
}

void Renderer::UpdateColor(unsigned int uniformBaseColor, unsigned int uniformAlpha, glm::vec4 baseColor)
{
	glUniform3fv(uniformBaseColor, 1, glm::value_ptr(glm::vec3(baseColor.r, baseColor.g, baseColor.b)));
	glUniform1fv(uniformAlpha, 1, &(baseColor.a));
}

void Renderer::UpdateStatus(unsigned int uniformStatus, bool status)
{
	glUniform1i(uniformStatus, status);
}

void Renderer::UpdateLight(unsigned int uniformLight, glm::vec3 light)
{
	glUniform3fv(uniformLight, 1, glm::value_ptr(light));
}

void Renderer::UpdateTexture(unsigned int uniformTexture, unsigned int textureId)
{
	glUniform1f(uniformTexture, (GLfloat)textureId);
}

void Renderer::UpdateFloatValue(unsigned int uniformFloat, float value)
{
	glUniform1f(uniformFloat, value);
}

void Renderer::UpdateIntValue(unsigned int uniformInt, int value)
{
	glUniform1i(uniformInt, value);
}

void Renderer::UpdateCameraView(unsigned int uniformView, glm::vec3 position)
{
	glUniform3f(uniformView, position.x, position.y, position.z);
}
void Renderer::UpdateLightVec3(unsigned int uniformLightVec3, glm::vec3 light)
{
	glUniform3f(uniformLightVec3, light.x, light.y, light.z);
}
void Renderer::UpdateLightFloat(unsigned int uniformLightFloat, float value)
{
	glUniform1f(uniformLightFloat, value);
}
void Renderer::UpdateLightStatus(unsigned int uniformLightStatus, bool status)
{
	glUniform1i(uniformLightStatus, status);
}

unsigned int Renderer::GetUniform(unsigned int shaderId, const char* loc)
{
	return glGetUniformLocation(shaderId, loc);
}

void Renderer::SetView(glm::mat4 view)
{
	this->view = view;
}

void Renderer::SetProjection(glm::mat4 projection)
{
	this->projection = projection;
}

void Renderer::Draw(unsigned int VAO, unsigned int vertices)
{
	glBindVertexArray(VAO);

	if (vertices == 3) glDrawArrays(GL_TRIANGLES, 0, vertices);
	else glDrawElements(GL_TRIANGLES, vertices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Renderer::DrawLines(unsigned int VAO, unsigned int vertices)
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, vertices);
	glBindVertexArray(0);
}

void Renderer::BindDiffuseMap(unsigned int textureId)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Renderer::BindSpecularMap(unsigned int textureId)
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Renderer::TextureEnable()
{
	glEnable(GL_TEXTURE_2D);
}

void Renderer::TextureDisable()
{
	glDisable(GL_TEXTURE_2D);
}

void Renderer::TextureDelete(unsigned int uniformTexture, unsigned int& textureId)
{
	glDeleteTextures(uniformTexture, &textureId);
}

void Renderer::BlendEnable()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::BlendDisable()
{
	glDisable(GL_BLEND);
}

void Renderer::UseTexture(int number, unsigned int id)
{
	glActiveTexture(GL_TEXTURE0 + number);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Renderer::CleanTexture()
{
	glActiveTexture(GL_TEXTURE0);
}
