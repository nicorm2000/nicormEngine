#include "Model.h"
namespace MikkaiEngine
{
	Model::Model(Renderer* rend)
	{
		directory   =   ""			;
		baseNode	=   nullptr		;
		shader		= rend			;
	}
	Model::~Model()
	{
	}
	void Model::Draw(glm::mat4 modelMatrix, glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
	{
		unsigned int modelLoc = glGetUniformLocation(shader->GetShader()->GetShaderId(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		unsigned int viewLoc = glGetUniformLocation(shader->GetShader()->GetShaderId(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		unsigned int projectionLoc = glGetUniformLocation(shader->GetShader()->GetShaderId(), "projection");
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		for (unsigned int i = 0; i < baseNode->getMeshes().size(); i++)
			baseNode->getMeshes()[i]->Draw();
	}
}
