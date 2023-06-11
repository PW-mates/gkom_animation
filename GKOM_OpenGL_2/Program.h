#pragma once

#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <string>
#include <map>


enum class WorkingMode
{
	Frame,
	Preview,
	Render
};

class Program
{
public:

	Program();

	static void setProgramsDirectory(std::string programDirectory);
	static void setWorkingMode(WorkingMode mode);
	static std::string getProgramsDirectory();
	static WorkingMode getWorkingMode();
	static void setFrame(int frame);
	static int getFrame();
	static void setOutputDirectory(std::string outputDirectory);
	static std::string getOutputDirectory();

	GLuint GetID();

	void Activate();
	void Deactivate();

	GLuint GetUniformID(std::string uniformName);

	bool Load(std::string vertexShaderFilePath, std::string fragmentShaderShaderPath);

private:
	
	bool readFile(std::string filePath, std::string& content);

	bool compileShader(GLenum shaderType, GLuint* shader, std::string shaderSource);

	bool linkProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID);

	void setupUniforms();

	GLuint _programID;

	std::map<std::string, GLuint> _uniformsID;

	static std::string _programsDirectory;
	static WorkingMode _mode;
	static int _frame;
	static std::string _outputDirectory;
};

