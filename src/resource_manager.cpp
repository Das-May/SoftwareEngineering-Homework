#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION //定义STB_IMAGE_IMPLEMENTATION，预处理器会修改头文件，让其只包含相关的函数定义源码，相当于把.h文件变成.cpp文件
#include "stb_image.h"


// 实例化静态变量
std::map<std::string, Shader>       ResourceManager::Shaders;
std::map<std::string, Texture2D>    ResourceManager::Textures;
//typedef vector<Mesh> Model;
std::map<std::string, Model>    ResourceManager::Models;
string ResourceManager::currentName;
Parameter ResourceManager::Parameters;

Shader& ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture2D& ResourceManager::LoadTexture(const char* file, bool alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}

Texture2D& ResourceManager::GetTexture(std::string name)
{
    return Textures[name];
}

Model& ResourceManager::LoadModel(string const& path, std::string name)
{
    currentName = name;
    loadModel(path);
    return Models[name];
}

Model& ResourceManager::GetModel(std::string name)
{
    return Models[name];
}

Parameter ResourceManager::LoadParameter()
{
    //初始化
    Parameters.bag_parameter.clear();
    Parameters.enemy_parameter.clear();
    ifstream fin;
    istringstream iss;
    string s;
    double t;

    // 读取
    fin.open("Setup.txt");
    getline(fin, s);
    if (s[0] == '@')// 1.获取场景参数
    {
        while (getline(fin, s) && s[0] != '@')// 逐行读取，将每一行数据读取到字符串 s 中
        {
            iss.clear();
            iss.str(s);
            iss >> t;// 逐词读取，遍历每一行中的每个词 t
            Parameters.scene_parameter.width = t;
            iss >> t;
            Parameters.scene_parameter.length = 100;
        }  
    }
    cout << "成功读取场景参数" << endl;
    if (s[0] == '@')// 2.读取障碍物位置
    {
        while (getline(fin, s) && s[0] != '@')
        {
            iss.clear();
            iss.str(s);
            iss >> t; Parameters.scene_parameter.obstacles_postion_x.push_back(t);
            iss >> t; Parameters.scene_parameter.obstacles_postion_z.push_back(t);
        }
    }
    cout << "成功读取障碍物信息" << endl;
    if (s[0] == '@')// 3.读取角色信息
    {
        while (getline(fin, s) && s[0] != '@')
        {
            iss.clear();
            iss.str(s);
            iss >> t; Parameters.player_parameter.x = t;
            iss >> t; Parameters.player_parameter.z = t;
            iss >> t; Parameters.player_parameter.hp = t;
            iss >> t; Parameters.player_parameter.atk = t;
        }
    }
    cout << "成功读取角色信息" << endl;
    // 读取敌人信息
    if (s[0] == '@')
    {
        while (getline(fin, s) && s[0] != '@')
        {
            iss.clear();
            iss.str(s);
            double a, b, c, d;
            iss >> a; iss >> b; iss >> c; iss >> d;
            CharacterParameter e(a,b,c,d);
            iss >> t; Parameters.enemy_parameter.push_back(e);
        }
    }
    cout << "成功读取敌人信息" << endl;
    // 读取血包信息
    if (s[0] == '@')
    {
        while (getline(fin, s) && s[0] != '@')
        {
            iss.clear();
            iss.str(s);
            double a, b, c, d;
            iss >> a; iss >> b; iss >> c; iss >> d;
            CharacterParameter bag(a, b, c, d);
            iss >> t; Parameters.bag_parameter.push_back(bag);
        }
    }
    cout << "成功读取血包信息" << endl;
    cout << "----------------------------" << endl;
    fin.close();
    return Parameters;
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders删除所有着色器	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // 从gl上下文中删除所有纹理
    for (auto iter : Textures)
        glDeleteProgram(iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if (gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
    // 创建纹理对象
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // 加载图像数据（是char数组）
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);//翻转图片y轴
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data)
    {
        // 交给纹理对象，生成纹理
        texture.Generate(width, height, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // 释放图像数据
    stbi_image_free(data);
    return texture;
}

void ResourceManager::loadModel(string const& path)
{
    // 通过ASSIMP读取文件
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // 检查错误
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return ;
    }

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

// 以递归方式处理节点。处理位于节点上的每个网格，并在其子节点(如果有的话)上重复此过程
void ResourceManager::processNode(aiNode* node, const aiScene* scene)
{
    // 处理位于当前节点的每个网格
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // 节点对象只包含索引 来索引场景中的实际对象
        // the node object only contains indices to index the actual objects in the scene. 
        // 场景包含所有的数据，节点只是用来保持组织的东西(如节点之间的关系)
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Models[currentName].push_back(processMesh(mesh, scene));
    }
    // 在我们处理完所有的网格(如果有的话)之后，我们递归地处理每个子节点
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

Mesh ResourceManager::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill 将要被填充的数据结构
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    /* --- 遍历网格的每个顶点，填充vector<Vertex> vertices; --- */
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;// 定义在mesh类中的顶点结构体
        // 我们声明了一个占位符向量，因为assimp使用它自己的向量类，它不直接转换为glm的vec3类，所以我们首先将数据传输到这个占位符glm::vec3。
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions 顶点坐标
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals 法线
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates 纹理坐标
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // 一个顶点可以包含多达8个不同的纹理坐标. 因此，我们假设我们不会
            // 使用一个顶点可以有多个纹理坐标的模型，所以我们总是取第一个集合(0)
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent 切线方向
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent 副切线方向
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    /* --- 现在遍历网格的每个面(三角形面)并检索相应的顶点索引，填充vector<unsigned int> indices; --- */
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return Mesh(vertices, indices);
}
