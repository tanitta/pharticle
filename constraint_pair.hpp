#pragma once
namespace pharticle{
	class ConstraintPair {
		public:
			std::vector<pharticle::Particle*> particle_ptrs_;
			ConstraintPair(pharticle::Particle* p1_ptr, pharticle::Particle* p2_ptr){
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
	};
} // namespace pharticle
