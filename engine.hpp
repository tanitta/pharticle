#pragma once
#include <iostream>
namespace pharticle {
	class Engine {
		private:
			std::vector<Particle> particles_;
			pharticle::World world_;
		public:
			Engine():world_(){
			};
			virtual ~Engine(){};
			
			void add_particle(){
			};
	};
} // namespace pharticle
