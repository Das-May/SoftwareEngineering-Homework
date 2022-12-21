/******************************
* 这是我的作业《基于OpenGL实现的FPS游戏引擎》的代码
* 
* 
*/
#include <glad/glad.h>  // 这是配置OpenGL上下文的库
#include <GLFW/glfw3.h> // 这是配置渲染窗口的库

#include <iostream>		// 熟悉的 用于输入输出的库

#include "game.h"


// 声明函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height);			// 配置窗口（帧缓冲）大小的函数
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);	// 响应用户键盘输入的函数
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);



// 初始的窗口大小
const unsigned int SCREEN_WIDTH = 800;	// 宽
const unsigned int SCREEN_HEIGHT = 600;	// 高

// 游戏
Game fps(SCREEN_WIDTH, SCREEN_HEIGHT);

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

    // glfw: 窗口回调函数
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glfw: 告诉GLFW捕获我们的鼠标
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: 加载所有的OpenGL函数指针
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

   

    // OpenGL: 配置
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);                            // 开启深度测试
    //glEnable(GL_BLEND);                                 // 开启混合
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // 混合函数是 src + dest * (1-src)

    // 游戏: 初始化
    // ---------------
    fps.Init();

    // delta time variables 时间间隔变量
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))// 检测窗口是否关闭
    {
        // calculate delta time 计算时间间隔
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();//整理输入事件

        // manage user input 管理用户输入
        // -----------------
        fps.ProcessInput(deltaTime);
        

        // update game state 更新游戏状态
        // -----------------
        fps.Update(deltaTime);

        // render 渲染
        // -----------------
        glClearColor(0.3f, 0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清理缓冲

        fps.Render();

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
    // 将按键反馈给Game类
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
    // 确保视口匹配新的窗口尺寸
    // 注意宽度和高度将明显大于视网膜显示器上指定的高度
    glViewport(0, 0, width, height);
    fps.Width = width;
    fps.Height = height;
}
