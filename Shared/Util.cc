#include <Shared/Util.hh>

#include <cfenv>
#include <random>

std::mt19937 mt{std::random_device()()};
std::uniform_real_distribution<float> distribution{0, 1};

namespace shared
{

	float RandomFloat() 
	{
		float v = distribution(mt);
		return v;
	}

	int GetFloatExceptionFlags()
	{
		return FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW;
	}
}
