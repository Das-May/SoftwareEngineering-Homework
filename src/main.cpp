/******************************
* 这是我的作业《基于OpenGL实现的FPS游戏引擎》的代码
* 
* 
*/
#include <glad/glad.h>  // 这是配置OpenGL上下文的库
#include <GLFW/glfw3.h> // 这是配置渲染窗口的库

#include <iostream>		// 熟悉的 用于输入输出的库

#include "resource_manager.h"

// 声明函数
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
    ResourceManager::LoadShader("shaders/model_loading.vs", "shaders/model_loading.fs", nullptr, "着色器测试");
    Shader s = ResourceManager::GetShader("着色器测试");
    ResourceManager::LoadTexture("textures/top.jpg", false, "纹理测试");
    Texture2D t = ResourceManager::GetTexture("纹理测试");
    s.Use().SetInteger("texture1", 0);
    

    // 下面是抄的，别管
    // 配置VAO和VBO
    unsigned int quadVAO;//顶点数组对象
    unsigned int VBO;//顶点缓冲区对象
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
    // 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 绑定顶点数组对象
    glBindVertexArray(quadVAO); 
    glEnableVertexAttribArray(0);
    // 设定顶点属性指针
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    


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
        

        // update game state 更新游戏状态
        // -----------------
        

        // render 渲染
        // -----------------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        s.Use();                            //激活着色器

        glActiveTexture(GL_TEXTURE0);
        t.Bind();

        glBindVertexArray(quadVAO);         //绑定图元
        glDrawArrays(GL_TRIANGLES, 0, 6);   //画它
        glBindVertexArray(0);               //解绑
        

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
    // 确保视口匹配新的窗口尺寸
    // 注意宽度和高度将明显大于视网膜显示器上指定的高度
    glViewport(0, 0, width, height);
}
