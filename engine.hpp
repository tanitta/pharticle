#pragma once
#include <iostream>
namespace pharticle {
	class Engine {
		private:
			std::vector<Particle*> particle_ptrs_;
			std::vector<ConstraintPair> constraint_pairs_;
			
			pharticle::CollisionDetector collision_detector_;
			std::vector<ConstraintPair> collision_constraint_pairs_;
			
			pharticle::ConstraintSolver constraint_solver_;
			pharticle::Integrator integrator_;
			
		public:
			Engine():
				collision_detector_(particle_ptrs_,collision_constraint_pairs_),
				constraint_solver_(constraint_pairs_),
				integrator_(particle_ptrs_)
			{
				collision_detector_.set_func_reaction_force([](pharticle::Particle&, pharticle::Particle&){Eigen::Vector3d v(0,0,0); return v;});
			};
			virtual ~Engine(){};
			
			
			void update(){
				collision_constraint_pairs_.clear();
				collision_detector_.update();
				constraint_pairs_.insert(constraint_pairs_.end(), collision_constraint_pairs_.begin(), collision_constraint_pairs_.end());
				constraint_solver_.update();
				integrator_.update();
				clear_constraint_pairs();
				clear_particles();
			};
			
			void add(Particle& p){
				particle_ptrs_.push_back(&p);
			};
			
		private:
			void clear_particles(){
				particle_ptrs_.clear();
			};
			
		public:	
			void add(pharticle::ConstraintPair& pair){
				constraint_pairs_.push_back(pair);
			};
			
			
			void add_constraint_pair_consist_of(pharticle::Particle& p1, pharticle::Particle& p2, std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
				constraint_pairs_.push_back(pharticle::ConstraintPair(p1,p2,f));
			};
			
			void add_as_both_directions(pharticle::ConstraintPair& pair){
				constraint_pairs_.push_back(pair);
				constraint_pairs_.push_back(pharticle::ConstraintPair(*pair.particle_ptrs_[1],*pair.particle_ptrs_[0],pair.func_force_));
			};
			
			
			void add_constraint_pair_as_both_directions_consist_of(pharticle::Particle& p1, pharticle::Particle& p2, std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
				constraint_pairs_.push_back(pharticle::ConstraintPair(p1,p2,f));
				constraint_pairs_.push_back(pharticle::ConstraintPair(p2,p1,f));
			};
		private:	
			void clear_constraint_pairs(){
				constraint_pairs_.clear();
			};
		public:	
			void set_collision_reaction_force(std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
				collision_detector_.set_func_reaction_force(f);
			};
			
			std::vector<ConstraintPair> collision_pairs(){
				return collision_constraint_pairs_;
			}
	};
} // namespace pharticle
