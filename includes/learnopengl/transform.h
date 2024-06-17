#pragma once

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

struct Transform
{
public:
	glm::vec3 position = glm::vec3();
	glm::vec3 rotation = glm::vec3(); // In Euler angles.
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

public:
	Transform() {}
	Transform(glm::vec3 position) : position(position) {}
	Transform(glm::vec3 position, glm::vec3 rotation) : position(position), rotation(rotation) {}
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : position(position), rotation(rotation), scale(scale) {}

	glm::mat4 GetModelMatrix() const
	{
		glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), position);                                                                 // translation
		modelMatrix *= glm::mat4_cast(glm::quat(glm::vec3(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z)))); // rotation
		modelMatrix = glm::scale(modelMatrix, scale);                                                                                      // scale
		return modelMatrix;
	}
};