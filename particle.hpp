#pragma once
namespace pharticle {
	class Particle {
		public:
			int id_;
			double mass_;
			double radius_;
			Eigen::Vector3d position_;
			Eigen::Vector3d velocity_;
			Eigen::Vector3d acceleration_;
			
			Particle():id_(0),mass_(1),radius_(),position_(),velocity_(),acceleration_(){
				position_ << 0,0,0;
				velocity_ << 0,0,0;
				acceleration_ << 0,0,0;
			}
			
			virtual ~Particle(){};
			
			// Eigen::Vector3d GetCenter() const{
			// 	Eigen::Vector3d center;
			// 	return center;
			// };
			void integrate(){
				velocity_ += acceleration_;
				position_ += velocity_;
			}
	};
} // namespace pharticle

