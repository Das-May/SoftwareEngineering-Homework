#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

// ��������ƶ��ļ�������ѡ�����������Զ���ض��ڴ���ϵͳ�����뷽��
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Ĭ�����ֵ
const float YAW         = -90.0f;   //
const float PITCH       =  0.0f;    // 
const float SPEED       =  2.5f;    // �ƶ��ٶ�
const float SENSITIVITY =  0.1f;    // ƫ�����ж�
const float ZOOM        =  45.0f;   // �����ٶ�


// һ�����������࣬���ڴ������벢������Ӧ��ŷ���ǡ������;��󣬹�OpenGLʹ��
class Camera
{
public:
    // �������
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // ŷ����
    float Yaw;
    float Pitch;
    // �������
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // ��������ʼ���� ���캯��
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    
    // �ñ�����ʼ���� ���캯��
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // ����ʹ��ŷ���Ǻ�LookAt�������� ��ͼ����V
    glm::mat4 GetViewMatrix();

    // ������κ����Ƽ��̵�����ϵͳ���յ�����
    // �����������ENUM��ʽ���������(�Ӵ���ϵͳ�г������)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // ������������ϵͳ���յ����롣����x��y�����ϵ�ƫ��ֵ��
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);

    // ������������¼����յ����롣ֻ��Ҫ���봹ֱ���ᡣ
    void ProcessMouseScroll(float yoffset);

private:
    // �������ŷ���Ƕȼ���ǰ��ʸ��
    void updateCameraVectors();
};
#endif