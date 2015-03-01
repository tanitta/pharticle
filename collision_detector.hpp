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
		public:
			CollisionDetector(){
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
				if(detect_collision_from(particle, collidable_node)){
					//バウンディングボックスと衝突する場合
					if(collidable_node.nexts_.size()==0){
						// collidable_pairs
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
			
	};
} // namespace pharticle
