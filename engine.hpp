#pragma once
#include <iostream>
namespace pharticle {
	class Engine {
		private:
			std::vector<Particle*> particle_ptrs_;
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
			
			Engine():
				// particle_ptrs_(0),
				collision_detector_(particle_ptrs_,constraint_pairs_),
				constraint_solver_(constraint_pairs_),
				integrator_(particle_ptrs_)
			{
				collision_detector_.set_func_reaction_force([](pharticle::Particle&, pharticle::Particle&){Eigen::Vector3d v(0,0,0); return v;});
			};
			virtual ~Engine(){};
			
			
			void update(){
				std::cout<<"----------------"<<std::endl;
				collision_detector_.update();
				std::cout << "constraint_pairs_:" << constraint_pairs_.size() << std::endl;
				std::cout << "particles:" << particle_ptrs_[0]->position_[0] << std::endl;
				constraint_solver_.update();
				integrator_.update();
				constraint_pairs_.clear();
				
			};
			
			void draw(){
			};
			
			void add_particle_ptr(Particle& p){
				particle_ptrs_.push_back(&p);
			};
			
			void clear_particle_ptrs(){
				particle_ptrs_.clear();
			};
			
			void set_func_reaction_force(std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
				collision_detector_.set_func_reaction_force(f);
			};
			
			void add_constraint_pair(pharticle::ConstraintPair& pair){
				constraint_pairs_.push_back(pair);
			};
			
			void add_constraint_pair(pharticle::Particle* p1_ptr, pharticle::Particle* p2_ptr, std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
				constraint_pairs_.push_back(pharticle::ConstraintPair(p1_ptr,p2_ptr,f));
			};
			
			void add_constraint_pair_bdi(pharticle::Particle* p1_ptr, pharticle::Particle* p2_ptr, std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
				constraint_pairs_.push_back(pharticle::ConstraintPair(p1_ptr,p2_ptr,f));
				constraint_pairs_.push_back(pharticle::ConstraintPair(p2_ptr,p1_ptr,f));
			};
			// void set_func_force(std::string s, std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
			// }
	};
} // namespace pharticle
