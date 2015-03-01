#pragma once
namespace pharticle {
	//! 任意軸での位置の比較を行う
	/*!
	 * Particleの並び替えに使用
	 */
	class LessCenter {
		private:
			const int axis_;
		public:
			LessCenter(const int axis):axis_(axis){};
			virtual ~LessCenter(){};
			bool operator()(pharticle::Particle* a, pharticle::Particle* b){
				return a->position_[axis_] < b->position_[axis_];
			};
	};
	class CollidableNode {
		public:
			std::vector<CollidableNode> nexts_;
			std::vector<pharticle::Particle*> particle_ptrs_;
			Eigen::Vector3d box_size_max_;
			Eigen::Vector3d box_size_min_;	
			
			CollidableNode():
				box_size_min_(Eigen::Vector3d::Zero(3)),box_size_max_(Eigen::Vector3d::Zero(3)){};
			virtual ~CollidableNode(){};
			
			void Setup(std::vector<pharticle::Particle*> particle_ptrs){
				if(particle_ptrs.size() > 0){
					
				}
			};
			
			void make_node(std::vector<pharticle::Particle*>& particle_ptrs){
				//バウンディングボックスを設定し
				//最も長い軸を調べる
				int most_large_axis = 0;
				for(int axis = 0; axis < 3; axis++){
					//バウンディングボックス
					fit_box(particle_ptrs,axis);
					
					//もっとも長い軸を算出
					//バウンディングボックスから算出
					if(axis != 0){
						if (box_size_max_[axis] - box_size_min_[axis] > box_size_max_[axis-1] - box_size_min_[axis-1]) {
							most_large_axis = axis;
						}
					}
				}
				//axis sort
				//最も長い軸でソートを行う
				LessCenter less_center(most_large_axis);
				std::sort(particle_ptrs.begin(), particle_ptrs.end(), less_center);
				
				//最長軸で2分割し再帰
				devide(particle_ptrs,most_large_axis);
			};
			
			void fit_box(std::vector<pharticle::Particle*>& particle_ptrs, int axis){
				// バウンディングボックスの初期化
				box_size_min_[axis] = particle_ptrs[0]->position_[axis]-particle_ptrs[0]->radius_;
				box_size_max_[axis] = particle_ptrs[0]->position_[axis]+particle_ptrs[0]->radius_;
				//比較してフィッティング
				for (auto&& particle_ptr : particle_ptrs) {
					double radius_min = particle_ptr->position_[axis]-particle_ptr->radius_;
					double radius_max = particle_ptr->position_[axis]+particle_ptr->radius_;
					if(radius_min < box_size_min_[axis]){
						box_size_min_[axis] = radius_min;
					};
					if(radius_max > box_size_max_[axis]){
						box_size_max_[axis] = radius_max;
					};
				}
			}
			
			void devide(std::vector<pharticle::Particle*>& particle_ptrs, int axis){
				if(particle_ptrs.size() > 1){
					int partial_length = particle_ptrs.size()/2;
					std::vector<pharticle::Particle*> partial_particle_ptrs1(0);
					std::vector<pharticle::Particle*> partial_particle_ptrs2(0);
					
					for(int i = 0; i < particle_ptrs.size(); i++){
						if( i < partial_length ){
							partial_particle_ptrs1.push_back(particle_ptrs[i]);
						}else{
							partial_particle_ptrs2.push_back(particle_ptrs[i]);
						}
					}
					
					nexts_.push_back(CollidableNode());
					nexts_.push_back(CollidableNode());
					nexts_[0].make_node(partial_particle_ptrs1);
					nexts_[1].make_node(partial_particle_ptrs2);
				}else{
					particle_ptrs_ = particle_ptrs;
				}
			};
	};
} // namespace pharticle
