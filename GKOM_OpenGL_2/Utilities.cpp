#include "Utilities.h"

uint64_t getCurrentTime()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

GLuint LoadBox(GLenum* primitive, unsigned int* count)
{
	GLuint VBO;
	GLuint VAO;

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;
	};

	std::vector<glm::vec3> positions;
	// Front face
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	// Back face
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	// Top face
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	// Bottom face
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	// Left face
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(-1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(-1.0f, 1.0f, 1.0f));
	// Right face
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, 1.0f));
	positions.push_back(glm::vec3(1.0f, -1.0f, -1.0f));
	positions.push_back(glm::vec3(1.0f, 1.0f, -1.0f));

	std::vector<glm::vec3> colors;
	// Front face
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	// Back face
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	// Top face
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	// Bottom face
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	// Left face
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
	// Right face
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
	colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));

	std::vector<glm::vec3> normals;
	// Front face
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	// Back face
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	normals.push_back(glm::vec3(0.0f, 0.0f, -1.0f));
	// Top face
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	// Bottom face
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	normals.push_back(glm::vec3(0.0f, -1.0f, 0.0f));
	// Left face
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(-1.0f, 0.0f, 0.0f));
	// Right face
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	normals.push_back(glm::vec3(1.0f, 0.0f, 0.0f));

	std::vector<Vertex> BufferData;

	for (int i = 0; i < positions.size(); i++)
	{
		BufferData.push_back({ positions[i], colors[i], normals[i] });
	}

	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * BufferData.size(), BufferData.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(glm::vec3)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	*count = BufferData.size();
	*primitive = GL_TRIANGLES;

	return VAO;
}

/// <summary>
/// Load a model from a file with obj format
/// </summary>F
/// <param name="path">Path to the file</param>
/// <returns>VAO of the model</returns>
GLuint LoadObj(const std::string& path, GLenum* primitive, unsigned int* count, Material* material) {
	namespace fs = std::filesystem;
	struct Vertex {
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
	};

	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	std::vector<Vertex> vertices;

	std::ifstream file(path);
	std::string full_path = fs::absolute(path).string();

#ifdef _WIN32
	std::string directory = full_path.substr(0, full_path.find_last_of('\\'));
#else
	std::string directory = full_path.substr(0, full_path.find_last_of('/'));
#endif

	if (!file.is_open()) {
		std::cerr << "Unable to open file " << path << std::endl;
		return 0;
	}

	bool has_material = false;


	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string type;
		ss >> type;

		if (type == "v") {
			glm::vec3 vertex;
			ss >> vertex.x >> vertex.y >> vertex.z;
			temp_vertices.push_back(vertex);
		}
		else if (type == "vt") {
			glm::vec2 uv;
			ss >> uv.x >> uv.y;
			temp_uvs.push_back(uv);
		}
		else if (type == "vn") {
			glm::vec3 normal;
			ss >> normal.x >> normal.y >> normal.z;
			temp_normals.push_back(normal);
		}
		else if (type == "f") {
			std::vector<std::string> vertices_str;
			std::string vertex;
			while (ss >> vertex)
				vertices_str.push_back(vertex);

			if (vertices_str.size() < 3)
				continue;  // Ignore degenerate faces

			std::vector<unsigned int> vertexIndices(vertices_str.size());
			std::vector<unsigned int> uvIndices(vertices_str.size());
			std::vector<unsigned int> normalIndices(vertices_str.size());

			for (size_t i = 0; i < vertices_str.size(); i++) {
				sscanf(vertices_str[i].c_str(), "%d/%d/%d",
					&vertexIndices[i], &uvIndices[i], &normalIndices[i]);
				vertexIndices[i]--;  // OBJ indexing starts at 1, not 0
				uvIndices[i]--;
				normalIndices[i]--;
			}

			// Triangulate the face
			for (size_t i = 2; i < vertices_str.size(); i++) {
				vertices.push_back(
					Vertex{ temp_vertices[vertexIndices[0]],
							temp_uvs[uvIndices[0]],
							temp_normals[normalIndices[0]] });
				vertices.push_back(
					Vertex{ temp_vertices[vertexIndices[i - 1]],
							temp_uvs[uvIndices[i - 1]],
							temp_normals[normalIndices[i - 1]] });
				vertices.push_back(
					Vertex{ temp_vertices[vertexIndices[i]],
							temp_uvs[uvIndices[i]],
							temp_normals[normalIndices[i]] });
			}
		}
		else if (type == "mtllib") {
			has_material = true;
			std::string mtlfile;
			ss >> mtlfile;

			*material = LoadMtl(directory + "/" + mtlfile);
		}
		else if (type == "o") {
			std::string object;
			ss >> object;
		}
	}

	if (!has_material) {
		*material = DefaultMtl();
	}

	// For a basic implementation we consider that our primitive is GL_TRIANGLES
	*primitive = GL_TRIANGLES;
	*count = vertices.size();

	// Load into GPU and return GLuint
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Vertex texture coordinates
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	// Vertex normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	return VAO;
}

/// <summary>
/// Load a Material from a file with mtl format
/// </summary>
/// <param name="path">Path to the file</param>
/// <returns>Material</returns>
Material LoadMtl(const std::string& path)
{
	std::ifstream file(path);
	std::string line;
	Material currentMaterial;

	if (!file.is_open()) {
		std::cerr << "Unable to open file " << path << std::endl;
		return currentMaterial;
	}

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string token;
		ss >> token;

		if (token == "newmtl") {
			ss >> currentMaterial.name;
		}
		else if (token == "Ka") {
			ss >> currentMaterial.ambient.x >> currentMaterial.ambient.y >> currentMaterial.ambient.z;
		}
		else if (token == "Kd") {
			ss >> currentMaterial.diffuse.x >> currentMaterial.diffuse.y >> currentMaterial.diffuse.z;
		}
		else if (token == "Ks") {
			ss >> currentMaterial.specular.x >> currentMaterial.specular.y >> currentMaterial.specular.z;
		}
		else if (token == "Ns") {
			ss >> currentMaterial.shininess;
		}
	}
	return currentMaterial;
}


Material DefaultMtl()
{
	Material defaultMaterial;
	defaultMaterial.name = "default";
	defaultMaterial.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	defaultMaterial.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	defaultMaterial.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	defaultMaterial.shininess = 32.0f;

	return defaultMaterial;
}

PointLight DefaultPointLight()
{
	PointLight defaultPointLight;
	defaultPointLight.positionAnimation.insertKeyframe(0, glm::vec3(3.0f, 3.0f, 30.0f));
	defaultPointLight.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	defaultPointLight.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	defaultPointLight.specular = glm::vec3(0.8f, 0.8f, 0.8f);
	defaultPointLight.color = glm::vec3(0.5f, 0.5f, 1.0f);

	return defaultPointLight;
}

void LoadAnimation(std::string programDirectory, AppConfig* appConfig, Camera* camera, std::vector<PointLight>* lights, std::vector<Object>* objects)
{
	std::string file_path = programDirectory + "/animation.json";

	std::ifstream file(file_path);
	json data = json::parse(file);

	appConfig->duration = data["duration"];
	appConfig->previewFps = data["previewFps"];
	appConfig->renderFps = data["prodFps"];

	// get the list of objects
	json objects_data = data["objects"];

	// iterate over the list of objects
	for (json::iterator it = objects_data.begin(); it != objects_data.end(); ++it) {
		std::string type = it.value()["type"];
		if (strcmp(type.c_str(), "camera") == 0) {
			// load camera
			camera->up = glm::vec3(0, 1, 0);
			camera->positionAnimation.clearKeyframes();
			camera->directionAnimation.clearKeyframes();
			for (json::iterator it2 = it.value()["keyframes"].begin(); it2 != it.value()["keyframes"].end(); ++it2) {
				int time = stoi(it2.key());
				for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) {
					if (strcmp(it3.key().c_str(), "position") == 0) {
						camera->positionAnimation.insertKeyframe(time, glm::vec3(it3.value()[0], it3.value()[1], it3.value()[2]));
					}
					else if (strcmp(it3.key().c_str(), "rotation") == 0) {
						camera->directionAnimation.insertKeyframe(time, glm::vec3(it3.value()[0], it3.value()[1], it3.value()[2]));
					}
				}
			}
		}
		else if (strcmp(type.c_str(), "light") == 0) {
			// load light
			PointLight light = DefaultPointLight();
			light.color = glm::vec3(it.value()["color"][0], it.value()["color"][1], it.value()["color"][2]);
			light.ambient = glm::vec3(it.value()["ambient"][0], it.value()["ambient"][1], it.value()["ambient"][2]);
			light.diffuse = glm::vec3(it.value()["diffuse"][0], it.value()["diffuse"][1], it.value()["diffuse"][2]);
			light.specular = glm::vec3(it.value()["specular"][0], it.value()["specular"][1], it.value()["specular"][2]);
			light.positionAnimation.clearKeyframes();
			for (json::iterator it2 = it.value()["keyframes"].begin(); it2 != it.value()["keyframes"].end(); ++it2) {
				int time = stoi(it2.key());
				for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) {
					if (strcmp(it3.key().c_str(), "position") == 0) {
						light.positionAnimation.insertKeyframe(time, glm::vec3(it3.value()[0], it3.value()[1], it3.value()[2]));
					}
				}
			}
			lights->push_back(light);
		}
		else if (strcmp(type.c_str(), "object") == 0) {
			// load object
			GLenum cubeVAOPrimitive;
			unsigned int cubeVAOVertexCount;
			Material cubeMaterial;
			std::string modelFile = it.value()["modelFile"];
			GLuint cubeVAO = LoadObj(programDirectory + "\\" + modelFile, &cubeVAOPrimitive, &cubeVAOVertexCount, &cubeMaterial);
			Object obj = Object(cubeVAO, cubeVAOPrimitive, cubeVAOVertexCount, cubeMaterial, glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
			obj.positionAnimation.clearKeyframes();
			obj.rotationAnimation.clearKeyframes();
			obj.scaleAnimation.clearKeyframes();
			for (json::iterator it2 = it.value()["keyframes"].begin(); it2 != it.value()["keyframes"].end(); ++it2) {
				int time = stoi(it2.key());
				for (json::iterator it3 = it2.value().begin(); it3 != it2.value().end(); ++it3) {
					if (strcmp(it3.key().c_str(), "position") == 0) {
						obj.positionAnimation.insertKeyframe(time, glm::vec3(it3.value()[0], it3.value()[1], it3.value()[2]));
					}
					else if (strcmp(it3.key().c_str(), "rotation") == 0) {
						obj.rotationAnimation.insertKeyframe(time, glm::vec3(it3.value()[0], it3.value()[1], it3.value()[2]));
					}
					else if (strcmp(it3.key().c_str(), "scale") == 0) {
						obj.scaleAnimation.insertKeyframe(time, glm::vec3(it3.value()[0], it3.value()[1], it3.value()[2]));
					}
				}
			}
			objects->push_back(obj);
		}
	}
}