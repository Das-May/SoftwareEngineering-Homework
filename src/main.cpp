/******************************
* �����ҵ���ҵ������OpenGLʵ�ֵ�FPS��Ϸ���桷�Ĵ���
* 
* 
*/
#include <glad/glad.h>  // ��������OpenGL�����ĵĿ�
#include <GLFW/glfw3.h> // ����������Ⱦ���ڵĿ�

#include <iostream>		// ��Ϥ�� ������������Ŀ�

#include "resource_manager.h"

// ��������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);			// ���ô��ڣ�֡���壩��С�ĺ���
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);	// ��Ӧ�û���������ĺ���


// ��ʼ�Ĵ��ڴ�С
const unsigned int SCREEN_WIDTH = 800;	// ��
const unsigned int SCREEN_HEIGHT = 600;	// ��

int main(int argc, char* argv[])
{
    // glfw: ���ڳ�ʼ��������
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // ������ʹ�õ���Ͱ汾 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  // ������ʹ�õ���߰汾 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Little FPS Game Enginee", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: �������е�OpenGL����ָ��
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // glfw: ���ڻص�����
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL: ����
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ��Ϸ: ��ʼ��
    // ---------------
    ResourceManager::LoadShader("shaders/model_loading.vs", "shaders/model_loading.fs", nullptr, "��ɫ������");
    Shader s = ResourceManager::GetShader("��ɫ������");
    ResourceManager::LoadTexture("textures/top.jpg", false, "�������");
    Texture2D t = ResourceManager::GetTexture("�������");
    s.Use().SetInteger("texture1", 0);
    

    // �����ǳ��ģ����
    // ����VAO��VBO
    unsigned int quadVAO;//�����������
    unsigned int VBO;//���㻺��������
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);
    // �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // �󶨶����������
    glBindVertexArray(quadVAO); 
    glEnableVertexAttribArray(0);
    // �趨��������ָ��
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    


    // delta time variables ʱ��������
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))// ��ⴰ���Ƿ�ر�
    {
        // calculate delta time ����ʱ����
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();//���������¼�

        // manage user input �����û�����
        // -----------------
        

        // update game state ������Ϸ״̬
        // -----------------
        

        // render ��Ⱦ
        // -----------------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        s.Use();                            //������ɫ��

        glActiveTexture(GL_TEXTURE0);
        t.Bind();

        glBindVertexArray(quadVAO);         //��ͼԪ
        glDrawArrays(GL_TRIANGLES, 0, 6);   //����
        glBindVertexArray(0);               //���
        

        glfwSwapBuffers(window);
    }

    // ������ֹ֮�󣬻�����Դ
    // ---------------------------------------------------------

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // ���û�����Esc��ʱ���رճ���
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ȷ���ӿ�ƥ���µĴ��ڳߴ�
    // ע���Ⱥ͸߶Ƚ����Դ�������Ĥ��ʾ����ָ���ĸ߶�
    glViewport(0, 0, width, height);
}
