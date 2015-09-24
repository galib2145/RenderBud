#ifndef UTILS_H
#define UTILS_H

float degreeToRadian(const float &degree);
float clamp(const float &lo, const float &hi, const float &v);
bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1) ;

struct Rng
{
    unsigned int m_z, m_w;

    Rng(unsigned int z = 362436069, unsigned int w = 521288629) : m_z(z), m_w(w) { }

    float nextFloat()
    {
        unsigned int i = nextUInt32();
        return i * 2.328306e-10f;
    }

    unsigned int nextUInt32()
    {
        m_z = 36969 * (m_z & 65535) + (m_z >> 16);
        m_w = 18000 * (m_w & 65535) + (m_w >> 16);
        return (m_z << 16) + m_w;  /* 32-bit result */
    }
};

#endif // UTILS_H
