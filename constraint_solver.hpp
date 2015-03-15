#pragma once
namespace pharticle {
	class ConstraintSolver {
		private:
			std::vector<ConstraintPair>& constraint_pairs_ref_;
		public:
			ConstraintSolver(std::vector<ConstraintPair>& constraint_pairs_ref):
				constraint_pairs_ref_(constraint_pairs_ref){
			};
			
			virtual ~ConstraintSolver(){};
			
			void update(){
				for (auto&& constraint_pair : constraint_pairs_ref_) {
					constraint_pair.solve();
				}
			};
	};
} // namespace pharticle

