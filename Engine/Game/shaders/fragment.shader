#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Light
{
	vec3 color;
	bool enabled;
};

struct DirectionalLight
{
	vec3 color;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	bool enabled;
};

struct PointLight
{
	vec3 color;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
	bool enabled;
};

struct SpotLight
{
	PointLight pointLight;
	vec3 direction;
	float cutOff;
	float outerCutOff;
	bool enabled;
};

struct BaseMaterial
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct TextureMaterial
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

#define LIGHTS_MAX 3
uniform DirectionalLight directionalLight;
uniform PointLight pointLight[LIGHTS_MAX];
uniform SpotLight spotLight[LIGHTS_MAX];
uniform bool affectedLight;

uniform vec3 color;
uniform float a;

uniform bool useTexture;
uniform sampler2D baseTexture;
uniform BaseMaterial baseMaterial;
uniform TextureMaterial textureMaterial;

uniform vec3 viewPosition;

vec3 CalculateDirLight(vec3 norm, vec3 viewDir, BaseMaterial material);
vec3 CalculatePointLight(PointLight pLight, vec3 norm, vec3 fPos, vec3 viewDir, BaseMaterial material);
vec3 CalculateSpotLight(SpotLight sLight, vec3 norm, vec3 fPos, vec3 viewDir, BaseMaterial material);

void main()
{
	BaseMaterial material = BaseMaterial(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f), 0.f);
	vec3 resultColor = vec3(0.f, 0.f, 0.f);
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPosition - FragPos);

	if (useTexture)
	{
		material.ambient = vec3(texture(textureMaterial.diffuse, TexCoord));
		material.diffuse = vec3(texture(textureMaterial.diffuse, TexCoord));
		material.specular = vec3(texture(textureMaterial.specular, TexCoord));
		material.shininess = textureMaterial.shininess;
	}
	else
	{
		material = baseMaterial;
	}

	if (affectedLight == true)
	{
		if (directionalLight.enabled == true)
		{
			resultColor += CalculateDirLight(norm, viewDir, material);
		}
		for (int i = 0; i < LIGHTS_MAX; i++)
		{
			if (pointLight[i].enabled == true)
			{
				resultColor += CalculatePointLight(pointLight[i], norm, FragPos, viewDir, material);
			}
			if (spotLight[i].enabled == true)
			{
				resultColor += CalculateSpotLight(spotLight[i], norm, FragPos, viewDir, material);
			}
		}
	}
	else
	{
		resultColor = color;
	}

	if (useTexture)
	{
		FragColor = texture(baseTexture, TexCoord) * vec4(resultColor, a);
	}
	else
	{
		FragColor = vec4(resultColor, a);
	}
}

vec3 CalculateDirLight(vec3 norm, vec3 viewDir, BaseMaterial material)
{
	vec3 lightDir = normalize(-directionalLight.direction);
	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	vec3 ambient = directionalLight.ambient * material.ambient * directionalLight.color;
	vec3 diffuse = directionalLight.diffuse * diff * material.diffuse * directionalLight.color;
	vec3 specular = directionalLight.specular * spec * material.specular * directionalLight.color;

	vec3 result = (ambient + diffuse + specular) * color;
	return result;
}

vec3 CalculatePointLight(PointLight pLight, vec3 norm, vec3 fPos, vec3 viewDir, BaseMaterial material)
{
	vec3 lightDir = normalize(pLight.position - fPos);

	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	float distance = length(pLight.position - fPos);
	float attenuation = 1.0f / (pLight.constant + pLight.linear * distance + pLight.quadratic * (distance * distance));

	vec3 ambient = pLight.ambient * material.ambient * pLight.color;
	vec3 diffuse = pLight.diffuse * diff * material.diffuse * pLight.color;
	vec3 specular = pLight.specular * spec * material.specular * pLight.color;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = (ambient + diffuse + specular) * color;
	return result;
}

vec3 CalculateSpotLight(SpotLight sLight, vec3 norm, vec3 fPos, vec3 viewDir, BaseMaterial material)
{
	vec3 lightDir = normalize(sLight.pointLight.position - fPos);

	float diff = max(dot(norm, lightDir), 0.0f);

	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);

	float distance = length(sLight.pointLight.position - fPos);
	float attenuation = 1.0f / (sLight.pointLight.constant + sLight.pointLight.linear * distance + sLight.pointLight.quadratic * (distance * distance));

	float theta = dot(lightDir, normalize(-sLight.direction));
	float epsilon = sLight.cutOff - sLight.outerCutOff;
	float intensity = clamp((theta - sLight.outerCutOff) / epsilon, 0.0f, 1.0f);

	vec3 ambient = sLight.pointLight.ambient * material.ambient * sLight.pointLight.color;
	vec3 diffuse = sLight.pointLight.diffuse * diff * material.diffuse * sLight.pointLight.color;
	vec3 specular = sLight.pointLight.specular * spec * material.specular * sLight.pointLight.color;
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;

	vec3 result = (ambient + diffuse + specular) * color;
	return result;
}