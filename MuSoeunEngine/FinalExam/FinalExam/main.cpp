#pragma comment(lib, "Opengl32.lib")

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <cmath>
#include <vector>
#include "Object.h"

const GLint WIDTH = 800, HEIGHT = 600;
const float BOTTOM_OFFSET = 100.0f; // 창 하단에서 100cm

void errorCallback(int error, const char* description)
{
    printf("GLFW Error: %s\n", description);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // 키 입력 처리 함수
}

int Physics()
{
    return 0;
}

int Initialize()
{
    return 0;
}

int Update(EnemyBlock enemies[], int numEnemies, float speed) {
    for (int i = 0; i < numEnemies; ++i) {
        enemies[i].Update(speed);
    }

    return 0;
}

int Render(Player& player, Floor& floor, EnemyBlock enemies[], int numEnemies, float screenWidth, float screenHeight) {
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw objects
    player.Draw(screenWidth, screenHeight);
    floor.Draw(screenWidth, screenHeight);
    for (int i = 0; i < numEnemies; ++i) {
        enemies[i].Draw(screenWidth, screenHeight);
    }

    return 0;
}

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(WIDTH, HEIGHT, "Google Dino Run Copy Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

    Initialize();

    // 객체 생성 (센티미터 단위)
    Floor floor(0, HEIGHT - BOTTOM_OFFSET, WIDTH, BOTTOM_OFFSET);  // 바닥을 창 하단에서 100cm 위에 위치
    Player player(100, HEIGHT - BOTTOM_OFFSET - 50, 50);          // 플레이어를 바닥 위에 위치
    EnemyBlock enemies[3] = {
        EnemyBlock(800, HEIGHT - BOTTOM_OFFSET - 100, 50, 100),
        EnemyBlock(900, HEIGHT - BOTTOM_OFFSET - 100, 50, 100),
        EnemyBlock(1000, HEIGHT - BOTTOM_OFFSET - 300, 50, 300)
    };

    float speed = 5.0f;

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 30.0f / 255.0f, 100.0f / 255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        Physics();
        Update(enemies, 3, speed);

        Render(player, floor, enemies, 3, WIDTH, HEIGHT);

        std::this_thread::sleep_for(std::chrono::milliseconds(16));

        glfwSwapBuffers(window); // 이중 버퍼링으로 깜빡임 방지
    }

    glfwTerminate();
    return 0;
}
