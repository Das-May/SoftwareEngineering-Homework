#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// 定义相机移动的几个可能选项。用作抽象，以远离特定于窗口系统的输入方法
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// 默认相机值
const float YAW         = -90.0f;   //
const float PITCH       =  0.0f;    // 
const float SPEED       =  2.5f;    // 移动速度
const float SENSITIVITY =  0.1f;    // 偏移敏感度
const float ZOOM        =  45.0f;   // 滚轮速度


// 一个抽象的相机类，用于处理输入并计算相应的欧拉角、向量和矩阵，供OpenGL使用
class Camera
{
public:
    // 相机属性
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // 欧拉角
    float Yaw;
    float Pitch;
    // 相机操作
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // 用向量初始化的 构造函数
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    
    // 用标量初始化的 构造函数
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // 返回使用欧拉角和LookAt矩阵计算的 视图矩阵V
    glm::mat4 GetViewMatrix();

    // 处理从任何类似键盘的输入系统接收的输入
    // 接受相机定义ENUM形式的输入参数(从窗口系统中抽象出来)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // 处理从鼠标输入系统接收的输入。期望x和y方向上的偏移值。
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);

    // 处理从鼠标滚轮事件接收的输入。只需要输入垂直轮轴。
    void ProcessMouseScroll(float yoffset);

private:
    // 从相机的欧拉角度计算前方矢量
    void updateCameraVectors();
};
#endif