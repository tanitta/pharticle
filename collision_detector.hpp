#pragma once
#include <collidable_node.hpp>
namespace pharticle {
	//! 衝突判定を行う
	/*!
	 * 
	 */
	
	class CollisionDetector {
		private:
			pharticle::CollidableNode collidable_tree_;
			std::vector<pharticle::Particle*> particle_ptrs_;
			
			std::vector<ConstraintPair>& constraint_pairs_ref_;
			
			std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> func_reaction_force_;
		public:
			CollisionDetector(std::vector<ConstraintPair>& constraint_pairs_ref):
				constraint_pairs_ref_(constraint_pairs_ref){
			};
			virtual ~CollisionDetector(){};
			
			void set_particle(std::vector<pharticle::Particle>& particles){
				particle_ptrs_.clear();
				for (auto&& particle : particles) {
					particle_ptrs_.push_back(&particle);
				}
			}
			
			void update(std::vector<pharticle::Particle>& particles){
				set_particle(particles);
				collidable_tree_.update(particle_ptrs_);
				
				for (auto&& particle : particles) {
					search_tree(particle, collidable_tree_);
				}
			};
			
			void search_tree(pharticle::Particle& particle, pharticle::CollidableNode& collidable_node){
				if(detect_collision_from(particle, collidable_node)){//バウンディングボックスと衝突する場合
					if(collidable_node.nexts_.size()==0){//葉の場合
						// collidable_pairs
						if (particle.id_ != collidable_node.particle_ptrs_[0]->id_) {
							// std::cout << "very near :" <<particle.id_<<" :"<<collidable_node.particle_ptrs_[0]->id_<< std::endl;
							//detail
							if(detect_detail(particle, *collidable_node.particle_ptrs_[0])){
								constraint_pairs_ref_.push_back(pharticle::ConstraintPair(&particle,collidable_node.particle_ptrs_[0], func_reaction_force_));
							}
						}
					}else{//nodeの場合
						for (auto&&  p: collidable_node.nexts_) {
							search_tree(particle, p);
						}
					}
				
				}else{
					//バウンディングボックスと衝突しない場合
				
				}
			};
			
			bool detect_collision_from(pharticle::Particle& particle, pharticle::CollidableNode& collidable_node){
				for(int axis = 0; axis < 3; axis++){
					double radius_min = particle.position_[axis] - particle.radius_;
					double radius_max = particle.position_[axis] + particle.radius_;
					if(radius_max < collidable_node.box_size_min_[axis] || radius_min > collidable_node.box_size_max_[axis]){
						return false;
					}
				}
				return true;
			}
			
			bool detect_detail(pharticle::Particle& p1, pharticle::Particle& p2){
				double distance_square = 0;
				for (int axis = 0; axis < 3; axis++) {
					distance_square += (p1.position_[axis] - p2.position_[axis])*(p1.position_[axis] - p2.position_[axis]);
				}	
				if(distance_square < (p1.radius_ + p2.radius_)*(p1.radius_ + p2.radius_)){
					return true;
				}
				return false;
			};
			
			void set_func_reaction_force(std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f){
				func_reaction_force_ = f;
			};
	};
} // namespace pharticle
