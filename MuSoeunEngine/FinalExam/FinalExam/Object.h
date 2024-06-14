#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

// 센티미터를 픽셀로 변환하는 함수
inline float cmToPx(float cm) {
    return cm;
}

// 픽셀을 OpenGL 좌표로 변환하는 함수
inline float pxToOpenGLX(float px, float screenWidth) {
    return (2.0f * px / screenWidth) - 1.0f;
}

inline float pxToOpenGLY(float px, float screenHeight) {
    return 1.0f - (2.0f * px / screenHeight);
}

// Base class
class Object {
public:
    float x, y;
    float width, height;
    float r, g, b;
    

    Object(float x_cm = 0, float y_cm = 0, float width_cm = 1, float height_cm = 1, float r = 1, float g = 1, float b = 1)
        : x(cmToPx(x_cm)), y(cmToPx(y_cm)), width(cmToPx(width_cm)), height(cmToPx(height_cm)), r(r), g(g), b(b) {}

    virtual void OnCollisionEnter(Object& other) {
        std::cout << "Collision detected with another object.\n";
    }

    bool CheckCollision(Object& other) {
        return (x < other.x + other.width &&
            x + width > other.x &&
            y < other.y + other.height &&
            y + height > other.y);
    }

    virtual void Draw(float screenWidth, float screenHeight) {
        glColor3f(r, g, b);
        glBegin(GL_QUADS);
        glVertex2f(pxToOpenGLX(x, screenWidth), pxToOpenGLY(y, screenHeight));
        glVertex2f(pxToOpenGLX(x + width, screenWidth), pxToOpenGLY(y, screenHeight));
        glVertex2f(pxToOpenGLX(x + width, screenWidth), pxToOpenGLY(y + height, screenHeight));
        glVertex2f(pxToOpenGLX(x, screenWidth), pxToOpenGLY(y + height, screenHeight));
        glEnd();
    }
};

// Derived classes
class Player : public Object {
public:
    Player(float x_cm = 0, float y_cm = 0, float size_cm = 50)
        : Object(x_cm, y_cm, size_cm, size_cm, 1.0f, 0.0f, 0.0f) {}

    void OnCollisionEnter(Object& other) override {
        std::cout << "Player collided with another object.\n";
    }

    void Draw(float screenWidth, float screenHeight) override {
        Object::Draw(screenWidth, screenHeight);

        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(pxToOpenGLX(x, screenWidth), pxToOpenGLY(y, screenHeight));
        glVertex2f(pxToOpenGLX(x + width, screenWidth), pxToOpenGLY(y, screenHeight));
        glVertex2f(pxToOpenGLX(x + width, screenWidth), pxToOpenGLY(y + height, screenHeight));
        glVertex2f(pxToOpenGLX(x, screenWidth), pxToOpenGLY(y + height, screenHeight));
        glEnd();
    }
};

class Floor : public Object {
public:
    Floor(float x_cm = 0, float y_cm = 0, float width_cm = 800, float height_cm = 50)
        : Object(x_cm, y_cm, width_cm, height_cm, 1.0f, 0.78f, 0.06f) {}

    void OnCollisionEnter(Object& other) override {
        std::cout << "Floor collided with another object.\n";
    }
};

class EnemyBlock : public Object {
public:
    EnemyBlock(float x_cm = 0, float y_cm = 0, float width_cm = 50, float height_cm = 100)
        : Object(x_cm, y_cm, width_cm, height_cm, 0.0f, 1.0f, 0.0f) {}

    void OnCollisionEnter(Object& other) override {
        std::cout << "EnemyBlock collided with another object.\n";
    }

    void Update(float speed) {
        x -= speed;
        if (x < -width) {
            x = 800; // 화면 오른쪽 끝에서 재활용
        }
    }
};

class Star : public Object {
public:
    Star(float x_cm = 0, float y_cm = 0, float width_cm = 50, float height_cm = 50)
        : Object(x_cm, y_cm, width_cm, height_cm, 1.0f, 1.0f, 0.0f) {}

    void OnCollisionEnter(Object& other) override {
        std::cout << "Star collided with another object.\n";
    }
};

// AABB 충돌 검사 함수
bool PhysicsAABB(Object& A, Object& B) {
    if (A.CheckCollision(B)) {
        A.OnCollisionEnter(B);
        B.OnCollisionEnter(A);
        return true;
    }
    return false;
}