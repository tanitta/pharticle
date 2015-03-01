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
			CollidableNode(){};
			virtual ~CollidableNode(){};
	};
} // namespace pharticle
