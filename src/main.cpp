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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



// ��ʼ�Ĵ��ڴ�С
const unsigned int SCREEN_WIDTH = 800;	// ��
const unsigned int SCREEN_HEIGHT = 600;	// ��

// camera
/*Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;*/

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
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
    //
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            fps.Keys[key] = true;
        else if (action == GLFW_RELEASE)
        {
            fps.Keys[key] = false;
            //fps.KeysProcessed[key] = false;
        }
    }
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // ȷ���ӿ�ƥ���µĴ��ڳߴ�
    // ע���Ⱥ͸߶Ƚ����Դ�������Ĥ��ʾ����ָ���ĸ߶�
    glViewport(0, 0, width, height);
}
