#ifndef MATH_H
#define MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Math {
public:

	/*Length of vector*/
	static float _length(const glm::vec3 &v);

	/*Square of triangle*/
	static float _square(const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3);

	/*Normalize vector*/
	static glm::vec3 normalize(const glm::vec3 &v);

	/*Point in triangle test*/
	static bool intersectionTrglPn(const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3, const glm::vec2 &pn);

	/*Scalar product of 2 vectors in space*/
	static float scalarPrt3(const glm::vec3 &a, const glm::vec3 &b);

	/*Scalar product of 2 vectors on plane*/
	static float scalarPrt2(const glm::vec2 &a, const glm::vec2 &b);

	/*Cross product of 2 vectors*/
	static glm::vec3 crossPrt(const glm::vec3 &v1, const glm::vec3 &v2);

	/*Rotate vector on SCENE_ROTATE angles*/
	static glm::vec3 rotate(const glm::vec3 &pn, float alpha, float beta, float zet);

};

#endif // !MATH_H