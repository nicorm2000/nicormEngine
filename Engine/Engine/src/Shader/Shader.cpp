#include "Shader.h"

Shader::Shader()
{
	shaderId = 0;
}

Shader::~Shader()
{
	glDeleteProgram(shaderId);
}

void Shader::CreateShader(string vertexPath, string fragmentPath)
{
	shaderId = glCreateProgram();

	if (!shaderId)
	{
		cout << "Error: Creating the shader program" << endl;
		return;
	}

	VertexShader(vertexPath);
	FragmentShader(fragmentPath);
	LinkShader();
}

void Shader::VertexShader(string vertexPath)
{
	int success;
	char infoLog[512];

	// Se almacena el shader en si
	string vertexShaderString = ReadShaderFile(vertexPath);

	// Se almacena el shader, pero en un array de chars
	const char* vertexShaderSource = vertexShaderString.c_str();

	// Se crea un shader (por el momento vacio) especificando que es Vertex
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// 1 Se indica qué shader va a modificarse
	// 2 Se indica la cantidad de elementos a modificar
	// 3 Se indica el texto por el cuál se reemplazará la información del shader
	// 4 Se especifica el largo del texto que se debe utilizar
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	// Compila el shader con la información brindada en el source
	glCompileShader(vertexShader);

	// Devuelve un parámetro del shader
	// 1 Se indica el shader del que se quiere comprobar el estado
	// 2 Se indica qué es lo que se quiere buscar (en este caso, el estado de compilación)
	// 3 Se pasa como referencia el puntero de la variable en la que quiero recibir el estado de compilación
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		// Devuelve el log de información del shader
		// 1 Se indica el shader del que se quiere recibir la info
		// 2 Se indica el tamaño máximo de lo que se busca mostrar (en este caso, el log tiene 512)
		// 3 Devuelve el tamaño real de lo que se recibe 
		// 4 Se indica el string donde se guardará el log
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);

		cout << "ERROR: Vertex shader compilation failed: " << infoLog << endl;
	};

	// Agrega el shader al programa anteriormente creado.
	glAttachShader(shaderId, vertexShader);
}

void Shader::FragmentShader(string fragmentPath)
{
	// Esto es exáctamente igual al Vertex Shader pero cambiando los paths y referencias a fragment
	int success;
	char infoLog[512];
	string fragmentShaderString = ReadShaderFile(fragmentPath);
	const char* fragmentShaderSource = fragmentShaderString.c_str();

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
		cout << "ERROR: Fragment shader compilation failed: " << infoLog << endl;
	};

	glAttachShader(shaderId, fragmentShader);
}

void Shader::LinkShader()
{
	// Es el último eslabón de la cadena del shader. Gracias a esto, es que se puede ejecutar el shader mismo.
	int success;
	char infoLog[512];

	// Crea el programa con los shaders cargados.
	glLinkProgram(shaderId);

	// Devuelve un parámetro del programa
	// 1 Se indica el programa del que se quiere comprobar un parámetro
	// 2 Se indica qué es lo que se quiere buscar (en este caso, el estado de linkeo)
	// 3 Se pasa como referencia el puntero de la variable en la que quiero recibir el estado de linkeo
	glGetProgramiv(shaderId, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
		cout << "ERROR: Program shader linking failed: " << infoLog << endl;
	}

	// Se busca que el programa esté en óptimas condiciones para poder funcionar
	glGetProgramiv(shaderId, GL_VALIDATE_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderId, sizeof(infoLog), NULL, infoLog);
		cout << "Error: Validating program: " << infoLog << endl;
		return;
	}

	// Genera los ejecutables de los distintos shaders cargados en el programa.
	// Esto solamente es posible cuando se COMPILARON los shaders, se CARGARON en el programa y se LINKEO el programa.
	glUseProgram(shaderId);

}

unsigned int Shader::GetShaderId()
{
	return shaderId;
}

string Shader::ReadShaderFile(string path)
{
	// Devuelve la información de un archivo de shader
	string shaderCode; // Contiene la informacion del shader
	ifstream vShaderFile; // Esto es un input/output confirmado, en base a eso, hace cosas

	// Failbit: recibir un dato erroneo.
	// Badbit: tener un error de logica.
	// Exceptions se fija si hay alguno de esos errores y tira el error.
	vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

	try
	{
		// Intenta abrir el archivo donde se encuentra el shader
		vShaderFile.open(path);
		stringstream vShaderStream;

		// rdbuf obtiene un puntero al filebuf
		// Se agrega la informacion del shaderFile al ShaderStream

		vShaderStream << vShaderFile.rdbuf();
		vShaderFile.close();

		// Se parsea el contenido del stream a string
		shaderCode = vShaderStream.str();
	}
	catch (ifstream::failure& e)
	{
		cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
	}

	return shaderCode;
}