#pragma once
namespace pharticle {
	class Integrator {
		private:
			std::vector<Particle*>& particle_ptrs_ref_;
		public:
			Integrator(std::vector<Particle*>& particle_ptrs_ref):particle_ptrs_ref_(particle_ptrs_ref){};
			virtual ~Integrator(){};
			
			void update(){
				for (auto&& particle_ptr : particle_ptrs_ref_) {
					particle_ptr->integrate();
					particle_ptr->acceleration_ << 0,0,0;
				}
			};
	};
} // namespace pharticle
