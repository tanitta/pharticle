#pragma once
namespace pharticle {
	class Integrator {
		private:
			std::vector<Particle>& particles_ref_;
		public:
			Integrator(std::vector<Particle>& particles_ref):particles_ref_(particles_ref){};
			virtual ~Integrator(){};
			
			void update(){
				for (auto&& particle : particles_ref_) {
					particle.integrate();
					particle.acceleration_ << 0,0,0;
				}
			};
	};
} // namespace pharticle
