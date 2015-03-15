#pragma once
#include <iostream>
namespace pharticle {
	class Engine {
		private:
			std::vector<Particle>& particles_;
			std::vector<ConstraintPair> constraint_pairs_;
			
			
			std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> func_reaction_force_;
			// std::map<std::string,std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)>> func_force_maps_;
			// 
			pharticle::CollisionDetector collision_detector_;
			
		public:
			Engine(std::vector<pharticle::Particle>& particles):
				particles_(particles),
				collision_detector_(constraint_pairs_)
			{
				set_func_reaction_force([](pharticle::Particle&, pharticle::Particle&){Eigen::Vector3d v(0,0,0); return v;});
			};
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
			
			void set_func_reaction_force(std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
				func_reaction_force_ = f;
			};
			
			// void set_func_force(std::string s, std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
			// }
	};
} // namespace pharticle
