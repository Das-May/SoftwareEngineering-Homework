/******************************
* 这是我的作业《基于OpenGL实现的FPS游戏引擎》的代码
* 
* 
*/
#include <glad/glad.h>  // 这是配置OpenGL上下文的库
#include <GLFW/glfw3.h> // 这是配置渲染窗口的库

#include <iostream>		// 熟悉的 用于输入输出的库

void framebuffer_size_callback(GLFWwindow* window, int width, int height);			// 配置窗口（帧缓冲）大小的函数
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);	// 响应用户键盘输入的函数


// 初始的窗口大小
const unsigned int SCREEN_WIDTH = 800;	// 宽
const unsigned int SCREEN_HEIGHT = 600;	// 高

int main(int argc, char* argv[])
{
    // glfw: 窗口初始化和配置
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);                  // 上下文使用的最低版本 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);                  // 上下文使用的最高版本 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Little FPS Game Enginee", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    // glad: 加载所有的OpenGL函数指针
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // glfw: 窗口回调函数
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL: 配置
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 游戏: 初始化
    // ---------------
    

    // delta time variables 时间间隔变量
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time 计算时间间隔
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // manage user input 管理用户输入
        // -----------------
        

        // update game state 更新游戏状态
        // -----------------
        

        // render 渲染
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        

        glfwSwapBuffers(window);
    }

    // 程序终止之后，回收资源
    // ---------------------------------------------------------

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // 当用户按下Esc键时，关闭程序
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
