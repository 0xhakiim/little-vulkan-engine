#include "two_bodies_simulation.hpp"
// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
namespace lve
{

	two_bodies::two_bodies() {
		loadGameObjects();
	}
	std::unique_ptr<LveModel> createCircleModel(LveDevice& device,  const unsigned int  numSides) {
		std::vector<LveModel::Vertex> uniqueVertices{};
		for (unsigned int i = 0; i < numSides; i++) {
			float angle = i * glm::two_pi<float>() / numSides;
			uniqueVertices.push_back({ {glm::cos(angle), glm::sin(angle)} });
		}
		uniqueVertices.push_back({});  // adds center vertex at 0, 0

		std::vector<LveModel::Vertex> vertices{};
		for ( unsigned int i = 0; i < numSides; i++) {
			vertices.push_back(uniqueVertices[i]);
			vertices.push_back(uniqueVertices[(i + 1) % numSides]);
			vertices.push_back(uniqueVertices[numSides]);
		}
		return std::make_unique<LveModel>(device, vertices);
	}
	std::unique_ptr<LveModel> createSquareModel(LveDevice& device, glm::vec2 offset) {
		std::vector<LveModel::Vertex> vertices = {
			{{-0.5f, -0.5f}},
			{{0.5f, 0.5f}},
			{{-0.5f, 0.5f}},
			{{-0.5f, -0.5f}},
			{{0.5f, -0.5f}},
			{{0.5f, 0.5f}},  //
		};
		for (auto& v : vertices) {
			v.position += offset;
		}
		return std::make_unique<LveModel>(device, vertices);
	}

	void two_bodies::run()
	{
		GravityPhysicsSystem gravitySystem{ 0.81f };
		Vec2FieldSystem vecFieldSystem{};

		SimpleRenderSystem simpleRenderSystem{ lveDevice, lveRenderer.getSwapChainRenderPass() };

		while (!lveWindow.shouldClose()) {
			glfwPollEvents();

			if (auto commandBuffer = lveRenderer.beginFrame()) {
				// update systems
				gravitySystem.update(physicsObjects, 1.f / 60, 5);
				vecFieldSystem.update(gravitySystem, physicsObjects, vectorField);

				// render system
				lveRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(commandBuffer, physicsObjects);
				simpleRenderSystem.renderGameObjects(commandBuffer, vectorField);
				lveRenderer.endSwapChainRenderPass(commandBuffer);
				lveRenderer.endFrame();
			}
		}

		vkDeviceWaitIdle(lveDevice.device());
	}

	

	void two_bodies::loadGameObjects()
	{
		std::shared_ptr<LveModel> circleModel = createCircleModel(__super::lveDevice, 30);
		std::shared_ptr<LveModel> squareModel = createSquareModel(__super::lveDevice, { 0.f, 0.f });
		auto red = LveGameObject::createGameObject();
		red.transform2d.scale = glm::vec2{ .05f };
		red.transform2d.translation = { .5f, .5f };
		red.color = { 1.f, 0.f, 0.f };
		red.rigidBody2d.velocity = { -.5f, .0f };
		red.model = circleModel;
		physicsObjects.push_back(std::move(red));
		auto blue = LveGameObject::createGameObject();
		blue.transform2d.scale = glm::vec2{ .05f };
		blue.transform2d.translation = { -.45f, -.25f };
		blue.color = { 0.f, 0.f, 1.f };
		blue.rigidBody2d.velocity = { .5f, .0f };
		blue.model = circleModel;
		physicsObjects.push_back(std::move(blue));
		int gridCount = 40;
		for (int i = 0; i < gridCount; i++) {
			for (int j = 0; j < gridCount; j++) {
				auto vf = LveGameObject::createGameObject();
				vf.transform2d.scale = glm::vec2(0.005f);
				vf.transform2d.translation = {
					-1.0f + (i + 0.5f) * 2.0f / gridCount,
					-1.0f + (j + 0.5f) * 2.0f / gridCount };
				vf.color = glm::vec3(1.0f);
				vf.model = squareModel;
				vectorField.push_back(std::move(vf));
			}
		}
	}
}
