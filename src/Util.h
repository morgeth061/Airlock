#pragma once
#ifndef __Util__
#define __Util__

#include "GLM/vec2.hpp"


class Util
{
public:
	Util();
	~Util();

	static const float EPSILON;
	static const float Deg2Rad;
	static const float Rad2Deg;

	static float sign(float value);
	static float clamp(float value, float min, float max);
	static float clamp01(float value);
	static float distance(glm::vec2 vecA, glm::vec2 vecB);
	static float squaredDistance(glm::vec2 vecA, glm::vec2 vecB);
	static float magnitude(glm::vec2 vec);
	static float squaredMagnitude(glm::vec2 vec);
	static glm::vec2 limitMagnitude(glm::vec2 vector, float magnitude);
	static float lerp(float a, float b, float t);
	static float lerpUnclamped(float a, float b, float t);
	static float lerpAngle(float a, float b, float t);
	static float repeat(float t, float length);
	static float RandomRange(float min, float max);
	static float Sanitize(float value);
	static glm::vec2 min(glm::vec2 vecA, glm::vec2 vecB);
	static glm::vec2 max(glm::vec2 vecA, glm::vec2 vecB);
	static glm::vec2 negate(glm::vec2 vec);
	static glm::vec2 inverse(glm::vec2 vec);
	static glm::vec2 normalize(glm::vec2 vec);
	static float angle(glm::vec2 from, glm::vec2 to);
	static float dot(glm::vec2 lhs, glm::vec2 rhs);



};
#endif /* defined (__Util__) */
