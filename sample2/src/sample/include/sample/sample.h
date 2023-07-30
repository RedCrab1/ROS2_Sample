#include "common/common.h"
#include <memory>
class Sample{
	public:
		Sample();
		virtual ~Sample();
		void Publish();
	private:
		std::shared_ptr<CommonLib> lib_;
};
