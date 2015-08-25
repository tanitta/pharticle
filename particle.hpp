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
			
			bool b_static_;
			
			Particle():id_(0),mass_(1),radius_(1),position_(),velocity_(),acceleration_(),b_static_(false){
				position_ << 0,0,0;
				velocity_ << 0,0,0;
				acceleration_ << 0,0,0;
			}
			
			virtual ~Particle(){};
			
			// Eigen::Vector3d GetCenter() const{
			// 	Eigen::Vector3d center;
			// 	return center;
			// };
			void integrate(double unit_time = 1.0){
				if(b_static_){
					velocity_ << 0,0,0;
				}else{
					velocity_ += acceleration_ * unit_time;
					position_ += velocity_ * unit_time;
				}
			}
	};
} // namespace pharticle

