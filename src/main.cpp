/******************************
* �����ҵ���ҵ������OpenGLʵ�ֵ�FPS��Ϸ���桷�Ĵ���
* 
* 
*/
#include <glad/glad.h>  // ��������OpenGL�����ĵĿ�
#include <GLFW/glfw3.h> // ����������Ⱦ���ڵĿ�

#include <iostream>		// ��Ϥ�� ������������Ŀ�

#include "game.h"


// ��������
void framebuffer_size_callback(GLFWwindow* window, int width, int height);			// ���ô��ڣ�֡���壩��С�ĺ���
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);	// ��Ӧ�û���������ĺ���
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



// ��ʼ�Ĵ��ڴ�С
const unsigned int SCREEN_WIDTH = 800;	// ��
const unsigned int SCREEN_HEIGHT = 600;	// ��

// ��Ϸ
Game fps(SCREEN_WIDTH, SCREEN_HEIGHT);

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

    // glfw: ���ڻص�����
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glfw: ����GLFW�������ǵ����
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: �������е�OpenGL����ָ��
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

   

    // OpenGL: ����
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);                            // ������Ȳ���
    //glEnable(GL_BLEND);                                 // �������
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // ��Ϻ����� src + dest * (1-src)

    // ��Ϸ: ��ʼ��
    // ---------------
    fps.Init();

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
        fps.ProcessInput(deltaTime);
        

        // update game state ������Ϸ״̬
        // -----------------
        fps.Update(deltaTime);

        // render ��Ⱦ
        // -----------------
        glClearColor(0.3f, 0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������

        fps.Render();

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
    // ������������Game��
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            fps.Keys[key] = true;
        else if (action == GLFW_RELEASE)
            fps.Keys[key] = false;
    }
    
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    fps.xpos = static_cast<float>(xposIn);
    fps.ypos = static_cast<float>(yposIn);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT)
        fps.shooting = true;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ȷ���ӿ�ƥ���µĴ��ڳߴ�
    // ע���Ⱥ͸߶Ƚ����Դ�������Ĥ��ʾ����ָ���ĸ߶�
    glViewport(0, 0, width, height);
    fps.Width = width;
    fps.Height = height;
}
