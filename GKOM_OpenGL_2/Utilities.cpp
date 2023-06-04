#include "Utilities.h"

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
    positions.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
    // Back face
    positions.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
    // Top face
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
    // Bottom face
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    // Left face
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3(-1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3(-1.0f,  1.0f,  1.0f));
    // Right face
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f,  1.0f));
    positions.push_back(glm::vec3( 1.0f, -1.0f, -1.0f));
    positions.push_back(glm::vec3( 1.0f,  1.0f, -1.0f));

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
    normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f,  1.0f));
    // Back face
    normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    normals.push_back(glm::vec3( 0.0f,  0.0f, -1.0f));
    // Top face
    normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f,  1.0f,  0.0f));
    // Bottom face
    normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    normals.push_back(glm::vec3( 0.0f, -1.0f,  0.0f));
    // Left face
    normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
    // Right face
    normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));
    normals.push_back(glm::vec3( 1.0f,  0.0f,  0.0f));

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
GLuint LoadObj(const std::string& path, GLenum* primitive, unsigned int* count) {
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
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << path << std::endl;
        return 0;
    }

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
            std::string vertex1, vertex2, vertex3;
            ss >> vertex1 >> vertex2 >> vertex3;

            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            sscanf(vertex1.c_str(), "%d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0]);
            sscanf(vertex2.c_str(), "%d/%d/%d", &vertexIndex[1], &uvIndex[1], &normalIndex[1]);
            sscanf(vertex3.c_str(), "%d/%d/%d", &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

            Vertex vert1 = { temp_vertices[vertexIndex[0] - 1], temp_uvs[uvIndex[0] - 1], temp_normals[normalIndex[0] - 1] };
            Vertex vert2 = { temp_vertices[vertexIndex[1] - 1], temp_uvs[uvIndex[1] - 1], temp_normals[normalIndex[1] - 1] };
            Vertex vert3 = { temp_vertices[vertexIndex[2] - 1], temp_uvs[uvIndex[2] - 1], temp_normals[normalIndex[2] - 1] };

            vertices.push_back(vert1);
            vertices.push_back(vert2);
            vertices.push_back(vert3);
        }
        else if (type == "mtllib") {
            std::string mtlfile;
            ss >> mtlfile;
            std::cout << "Material library file: " << mtlfile << std::endl;
        }
        else if (type == "o") {
            std::string object;
            ss >> object;
            std::cout << "Object: " << object << std::endl;
        }
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