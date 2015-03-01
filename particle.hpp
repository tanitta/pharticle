#pragma once
namespace pharticle {
	class Particle {
		public:
			double mass_;
			double radius_;
			Eigen::Vector3d position_;
			Eigen::Vector3d velocity_;
			Eigen::Vector3d acceleration_;
			
			Particle():mass_(),radius_(),position_(),velocity_(),acceleration_(){
			}
			
			virtual ~Particle(){};
			
			// Eigen::Vector3d GetCenter() const{
			// 	Eigen::Vector3d center;
			// 	return center;
			// };
	};
} // namespace pharticle

