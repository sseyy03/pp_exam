#pragma once
#include <iostream>
namespace Transform
{
    struct Vertex
    {
        float x;
        float y;
    };

    struct Vector
    {
        float x_meter;
        float y_meter;
    };

    // 미터 단위로 이동
    Vertex MoveVertex(Vertex point, Vector meter) {
        point.x += meter.x_meter * 100; // 1m = 100cm
        point.y += meter.y_meter * 100;
        return point;
    }

    // 각도 단위로 회전 (시계 방향)
    Vertex RotateVertex(Vertex point, Vertex origin, float angle_degree) {
        float angle_rad = angle_degree * 3.14159265 / 180.0;
        float s = sin(angle_rad);
        float c = cos(angle_rad);

        
        point.x -= origin.x;
        point.y -= origin.y;

        float new_x = point.x * c + point.y * s;
        float new_y = -point.x * s + point.y * c;

        point.x = new_x + origin.x;
        point.y = new_y + origin.y;

        return point;
    }

    // 미터 단위로 배율 조정
    Vertex ScaleVertex(Vertex point, Vertex origin, Vector meter) {
        point.x = origin.x + (point.x - origin.x) * meter.x_meter;
        point.y = origin.y + (point.y - origin.y) * meter.y_meter;
        return point;
    }
}

