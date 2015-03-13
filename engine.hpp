#pragma once
#include <iostream>
namespace pharticle {
	class Engine {
		private:
			std::vector<Particle>& particles_;
			std::vector<ConstraintPair> constraint_pairs_;
			
			pharticle::CollisionDetector collision_detector_;
		public:
			Engine(std::vector<pharticle::Particle>& particles):
				particles_(particles),
				collision_detector_(constraint_pairs_)
			{};
			virtual ~Engine(){};
			
			void set_particle(){
			};
			
			void update(){
				std::cout<<"----------------"<<std::endl;
				collision_detector_.update(particles_);
				std::cout << "constraint_pairs_:" << constraint_pairs_.size() << std::endl;
				constraint_pairs_.clear();
			};
			
			void draw(){
			};
	};
} // namespace pharticle
