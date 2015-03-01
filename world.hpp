#pragma once
namespace pharticle {
	class World {
		public:
			double friction_coefficient_;
			World(){};
			virtual ~World(){};
	};
} // namespace pharticle
