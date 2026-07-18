#pragma once
#include "lve_model.hpp"


//std
#include <memory>
namespace lve
{
	struct Transform2dComponent {
		glm::vec3 translation{};
		glm::vec2 scale{ 1.f, 1.f };
		float rotation;
		glm::mat2 mat2() {
			const float s = sin(rotation);
			const float c = cos(rotation);
			glm::mat2 rotationMat{
				{c, s},
				{-s, c}
			};
			glm::mat2 scaleMat{
				{scale.x, 0.f},
				{0.f, scale.y}
			};
			return rotationMat * scaleMat;
		};
		
	};
	class LveGameObject
	{
	public:
		using id_t = unsigned int;

		LveGameObject(const LveGameObject&) = delete;
		LveGameObject& operator=(const LveGameObject&) = delete;
		LveGameObject(LveGameObject&&) = default;
		LveGameObject& operator=(LveGameObject&&) = default;
		static LveGameObject createGameObject() {
			static LveGameObject::id_t currentId = 0;
			return LveGameObject{ currentId++ };
		}
		id_t getId() { return id; };

		std::shared_ptr<LveModel> model{};
		glm::vec3 position{};
		glm::vec3 color{};
		Transform2dComponent transform2d{};
	private:
		id_t id{ 0 };
		LveGameObject(id_t objId) : id{ objId } {};


	};

}