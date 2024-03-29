#include "Framework.h"


namespace Framework
{
	GLuint CreateShader(GLenum eShaderType,
		const std::string &strShaderFile, const std::string &strShaderName)
	{   
		GLuint shader = glCreateShader(eShaderType);
		const char *strFileData = strShaderFile.c_str();
		glShaderSource(shader, 1, &strFileData, NULL);

		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			const char *strShaderType = NULL;

			switch(eShaderType)
			{
			    case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			    case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			    case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
            }

			fprintf(stderr, "Compile failure in %s shader named \"%s\". Error:\n%s\n",
				strShaderType, strShaderName.c_str(), strInfoLog);
			delete[] strInfoLog;
		}

		return shader;
	}

	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename)
	{
		std::string strFilename = strShaderFilename;
		std::ifstream shaderFile(strFilename.c_str());
		std::stringstream shaderData;
        shaderData << SHADER_VERSION_STRING;
		shaderData << shaderFile.rdbuf();
		shaderFile.close();
		

		return CreateShader(eShaderType, shaderData.str(), strShaderFilename);
	}
	
	GLuint CreateProgram(const std::vector<GLuint> &shaderList)
{
	GLuint program = glCreateProgram();

	for(size_t iLoop = 0; iLoop < shaderList.size(); iLoop++)
		glAttachShader(program, shaderList[iLoop]);

	glLinkProgram(program);

	GLint status;
	glGetProgramiv (program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}

	return program;
}
    void multiplyMatrix4x4(float* A, float* B, float* C){
        
        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                float v = 0;
                for(int k = 0; k<4; k++){
                    v += A[i+4*k]*B[k + 4*j];
                }
                
                C[i + 4*j] = v;
                
            }
        }
        
        
    }
    
    float* multiplyMatrixVector4(float* A, float* b){
        float* result = new float[4];
        for(int i = 0; i<4; i++){
            float s = 0;
            for(int j = 0; j<4; j++){
                s += A[4*j + i]*b[j];
            }
            result[i] = s;
        }
        
        return result;
    }
    
    



GLFWwindow* initializeWindow(){
        
    GLFWwindow* window;
        
    if (!glfwInit())  {
        exit( EXIT_FAILURE );
    }
        
        
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(640, 480, "Orbits", NULL, NULL);
    GetError();
    printf("to\n");
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        glfwTerminate();
        printf("Failed to initialize OpenGL context\n");
        return 0;
    }

	if (!window)
	{
		glfwTerminate();
		return 0;
	}
	printf("GLSL version %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("GL Version: %s\n", glGetString(GL_VERSION));

	glClearColor( 0.02f, 0.02f, 0.02f, 0.0f );
	glClearDepth( 1.0f );
    
    printf("setup\n");
        
	return window;
        
}

GLuint loadProgram(){
    //Load program.
    std::vector<GLuint> shaderList;

    shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "shaders/vertex.shader"));
    shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "shaders/fragment.shader"));
    GetError();
    return Framework::CreateProgram(shaderList);

}

GLuint loadBackgroundProgram(){
    std::vector<GLuint> shaderList;

    shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "shaders/background.vert"));
    shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "shaders/background.frag"));
    GetError();
    return Framework::CreateProgram(shaderList);
}
}
