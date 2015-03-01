#pragma once
#include <iostream>
namespace pharticle {
	class Engine {
		private:
			std::vector<Particle>& particles_;
			
			pharticle::CollisionDetector collision_detector_;
		public:
			Engine(std::vector<pharticle::Particle>& particles):
				particles_(particles),
				collision_detector_()
			{};
			virtual ~Engine(){};
			
			void set_particle(){
			};
			
			void update(){
				collision_detector_.update(particles_);
			};
	};
} // namespace pharticle
