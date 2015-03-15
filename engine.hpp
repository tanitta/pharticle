#pragma once
#include <iostream>
namespace pharticle {
	class Engine {
		private:
			std::vector<Particle>& particles_;
			std::vector<ConstraintPair> constraint_pairs_;
			
			
			// std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> func_reaction_force_;
			// std::map<std::string,std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)>> func_force_maps_;
			// 
			pharticle::CollisionDetector collision_detector_;
			pharticle::ConstraintSolver constraint_solver_;
			pharticle::Integrator integrator_;
			
		public:
			static Eigen::Vector3d add_default_reactive_force(pharticle::Particle& a, pharticle::Particle& b){
				Eigen::Vector3d v(0,0,0);
				return v;
			}
			
			Engine(std::vector<pharticle::Particle>& particles):
				particles_(particles),
				collision_detector_(constraint_pairs_),
				constraint_solver_(constraint_pairs_),
				integrator_(particles_)
			{
				collision_detector_.set_func_reaction_force([](pharticle::Particle&, pharticle::Particle&){Eigen::Vector3d v(0,0,0); return v;});
			};
			virtual ~Engine(){};
			
			void set_particle(){
			};
			
			void update(){
				std::cout<<"----------------"<<std::endl;
				collision_detector_.update(particles_);
				std::cout << "constraint_pairs_:" << constraint_pairs_.size() << std::endl;
				constraint_solver_.update();
				integrator_.update();
				constraint_pairs_.clear();
				
			};
			
			void draw(){
			};
			
			void set_func_reaction_force(std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
				collision_detector_.set_func_reaction_force(f);
			};
			
			// void set_func_force(std::string s, std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
			// }
	};
} // namespace pharticle
