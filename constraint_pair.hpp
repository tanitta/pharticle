#pragma once
namespace pharticle{
	class ConstraintPair {
		public:
			std::vector<pharticle::Particle*> particle_ptrs_;
			std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> func_force_;
			
			ConstraintPair(pharticle::Particle* p1_ptr, pharticle::Particle* p2_ptr, std::function<Eigen::Vector3d(pharticle::Particle&, pharticle::Particle&)> f):func_force_(f){
				particle_ptrs_.push_back(p1_ptr);
				particle_ptrs_.push_back(p2_ptr);
			};
			virtual ~ConstraintPair(){};
			
			bool has(pharticle::Particle* particle_ptr){
				for (auto&& p: particle_ptrs_) {
					if(p->id_ == particle_ptr->id_){
						return true;
					}
				}
				return false;
			};
			
			void solve(){
				particle_ptrs_[1]->acceleration_ += func_force_(*particle_ptrs_[0], *particle_ptrs_[1])/particle_ptrs_[0]->mass_;
			};
	};
} // namespace pharticle
