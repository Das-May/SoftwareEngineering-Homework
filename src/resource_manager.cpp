#include "resource_manager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION //����STB_IMAGE_IMPLEMENTATION��Ԥ���������޸�ͷ�ļ�������ֻ������صĺ�������Դ�룬�൱�ڰ�.h�ļ����.cpp�ļ�
#include "stb_image.h"


// ʵ������̬����
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
    //��ʼ��
    Parameters.bag_parameter.clear();
    Parameters.enemy_parameter.clear();
    ifstream fin;
    istringstream iss;
    string s;
    double t;

    // ��ȡ
    fin.open("Setup.txt");
    getline(fin, s);
    if (s[0] == '@')// 1.��ȡ��������
    {
        while (getline(fin, s) && s[0] != '@')// ���ж�ȡ����ÿһ�����ݶ�ȡ���ַ��� s ��
        {
            iss.clear();
            iss.str(s);
            iss >> t;// ��ʶ�ȡ������ÿһ���е�ÿ���� t
            Parameters.scene_parameter.width = t;
            iss >> t;
            Parameters.scene_parameter.length = 100;
        }  
    }
    cout << "�ɹ���ȡ��������" << endl;
    if (s[0] == '@')// 2.��ȡ�ϰ���λ��
    {
        while (getline(fin, s) && s[0] != '@')
        {
            iss.clear();
            iss.str(s);
            iss >> t; Parameters.scene_parameter.obstacles_postion_x.push_back(t);
            iss >> t; Parameters.scene_parameter.obstacles_postion_z.push_back(t);
        }
    }
    cout << "�ɹ���ȡ�ϰ�����Ϣ" << endl;
    if (s[0] == '@')// 3.��ȡ��ɫ��Ϣ
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
    cout << "�ɹ���ȡ��ɫ��Ϣ" << endl;
    // ��ȡ������Ϣ
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
    cout << "�ɹ���ȡ������Ϣ" << endl;
    // ��ȡѪ����Ϣ
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
    cout << "�ɹ���ȡѪ����Ϣ" << endl;
    cout << "----------------------------" << endl;
    fin.close();
    return Parameters;
}

void ResourceManager::Clear()
{
    // (properly) delete all shadersɾ��������ɫ��	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // ��gl��������ɾ����������
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
    // �����������
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // ����ͼ�����ݣ���char���飩
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);//��תͼƬy��
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data)
    {
        // �������������������
        texture.Generate(width, height, data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // �ͷ�ͼ������
    stbi_image_free(data);
    return texture;
}

void ResourceManager::loadModel(string const& path)
{
    // ͨ��ASSIMP��ȡ�ļ�
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // ������
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return ;
    }

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
}

// �Եݹ鷽ʽ����ڵ㡣����λ�ڽڵ��ϵ�ÿ�����񣬲������ӽڵ�(����еĻ�)���ظ��˹���
void ResourceManager::processNode(aiNode* node, const aiScene* scene)
{
    // ����λ�ڵ�ǰ�ڵ��ÿ������
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // �ڵ����ֻ�������� �����������е�ʵ�ʶ���
        // the node object only contains indices to index the actual objects in the scene. 
        // �����������е����ݣ��ڵ�ֻ������������֯�Ķ���(��ڵ�֮��Ĺ�ϵ)
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        Models[currentName].push_back(processMesh(mesh, scene));
    }
    // �����Ǵ��������е�����(����еĻ�)֮�����ǵݹ�ش���ÿ���ӽڵ�
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

Mesh ResourceManager::processMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill ��Ҫ���������ݽṹ
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    /* --- ���������ÿ�����㣬���vector<Vertex> vertices; --- */
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;// ������mesh���еĶ���ṹ��
        // ����������һ��ռλ����������Ϊassimpʹ�����Լ��������࣬����ֱ��ת��Ϊglm��vec3�࣬�����������Ƚ����ݴ��䵽���ռλ��glm::vec3��
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions ��������
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals ����
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates ��������
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // һ��������԰������8����ͬ����������. ��ˣ����Ǽ������ǲ���
            // ʹ��һ����������ж�����������ģ�ͣ�������������ȡ��һ������(0)
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent ���߷���
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent �����߷���
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    /* --- ���ڱ��������ÿ����(��������)��������Ӧ�Ķ������������vector<unsigned int> indices; --- */
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
