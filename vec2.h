#ifndef VEC2_H
#define VEC2_H

class vec2
{
private:
    float x;
    float y;

public:
    vec2() : x(0.0f), y(0.0f) {}
    vec2(float x) : x(x), y(x) {}
    vec2(float x, float y) : x(x), y(y) {}

    vec2 operator+(const vec2& other) const
    {
        return vec2(x + other.x, y + other.y);
    }

    vec2 operator-(const vec2& other) const
    {
        return vec2(x - other.x, y - other.y);
    }

    vec2 operator*(const vec2& other) const
    {
        return vec2(x * other.x, y * other.y);
    }

    vec2 operator/(const vec2& other) const
    {
        // Check if the divisor is zero
        if (other.x == 0.0f || other.y == 0.0f)
        {
            throw std::runtime_error("Division by zero");
        }
        return vec2(x / other.x, y / other.y);
    }

    vec2& operator+=(const vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    vec2& operator-=(const vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    vec2& operator*=(const vec2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    vec2& operator/=(const vec2& other)
    {
        // Check if the divisor is zero
        if (other.x == 0.0f || other.y == 0.0f)
        {
            throw std::runtime_error("Division by zero");
        }
        x /= other.x;
        y /= other.y;
        return *this;
    }

    vec2 operator-() const
	{
		return vec2(-x, -y);
	}

    void print() const
    {
        std::cout << x << ", " << y << std::endl;
    }
};

#endif // VEC2_H