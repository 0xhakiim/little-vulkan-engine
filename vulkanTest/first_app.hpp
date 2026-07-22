#pragma once

#include "lve_device.hpp"
#include "lve_pipeline.hpp"
#include "lve_window.hpp"
#include "lve_game_object.hpp"
#include "lve_renderer.hpp"

// std
#include <memory>
#include <vector>

namespace lve {
	class FirstApp {
	public:
		static constexpr int WIDTH = 800;
		static constexpr int HEIGHT = 600;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator=(const FirstApp&) = delete;

		virtual void run();

	private:
		virtual void loadGameObjects();
		void createPipelineLayout();
		void createPipeline();
		
		
		
		void sierpinski(std::vector<LveModel::Vertex>& vertices, int depth, glm::vec3 left, glm::vec3 right, glm::vec3 top);
	protected:
		LveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
		LveDevice lveDevice{ lveWindow };
		LveRenderer lveRenderer{ lveWindow, lveDevice };

		
		std::vector<LveGameObject> gameObjects;
		
	};
}  // namespace lve