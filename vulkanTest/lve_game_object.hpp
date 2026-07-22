#pragma once
#include "lve_model.hpp"

//libs
#include <glm/gtc/matrix_transform.hpp>
//std
#include <memory>
namespace lve
{
	struct TransformComponent {
		glm::vec3 translation{};
		glm::vec3 scale{ 1.f, 1.f, 1.f };
		glm::vec3 rotation;
		glm::mat4 mat4() {
			auto transform = glm::translate(glm::mat4{ 1.f }, translation);
			transform = glm::scale(transform, scale);
			transform = glm::rotate(transform, rotation.y,{0.f ,1.f,0.f});
			transform = glm::rotate(transform, rotation.x,{1.f ,0.f,0.f});
			transform = glm::rotate(transform, rotation.z,{0.f ,0.f,1.f});
			return transform;
		};
		
	};
	struct RigidBody2dComponent {
		glm::vec3 velocity;
		float mass{ 1.0f };
	};
	class LveGameObject
	{
	public:
		using id_t = unsigned int;
		 
		
		static LveGameObject createGameObject() {
			static LveGameObject::id_t currentId = 0;
			return LveGameObject{ currentId++ };
		}
		id_t getId() { return id; };

		std::shared_ptr<LveModel> model{};
		glm::vec3 position{};
		glm::vec3 color{};
		TransformComponent transform2d{};
		RigidBody2dComponent rigidBody2d{};
	private:
		id_t id{ 0 };
		LveGameObject(id_t objId) : id{ objId } {};


	};

}