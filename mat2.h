#pragma once
#include "vec2.h"

class mat2 {

public:
    float m[2][2];

    mat2() {
        m[0][0] = 0.0f; m[0][1] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 0.0f;
    }

    mat2(float m00, float m01, float m10, float m11) {
        m[0][0] = m00; m[0][1] = m01;
        m[1][0] = m10; m[1][1] = m11;
    }

    float& operator()(int row, int col) {
        return m[row][col];
    }

    const float& operator()(int row, int col) const {
        return m[row][col];
    }

    mat2 operator+(const mat2& other) const {
        return mat2(
            m[0][0] + other.m[0][0], m[0][1] + other.m[0][1],
            m[1][0] + other.m[1][0], m[1][1] + other.m[1][1]
        );
    }

    mat2 operator-(const mat2& other) const {
        return mat2(
            m[0][0] - other.m[0][0], m[0][1] - other.m[0][1],
            m[1][0] - other.m[1][0], m[1][1] - other.m[1][1]
        );
    }

    mat2 operator*(const mat2& other) const {
        return mat2(
            m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0], m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1],
            m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0], m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1]
        );
    }

    mat2 operator*(float scalar) const {
        return mat2(
            m[0][0] * scalar, m[0][1] * scalar,
            m[1][0] * scalar, m[1][1] * scalar
        );
    }

    friend mat2 operator*(float scalar, const mat2& m) {
        return m * scalar;
    }
};