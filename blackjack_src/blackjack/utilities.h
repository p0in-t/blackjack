#pragma once
#include <random>
#include <iostream>

namespace Utils
{
	inline int GenerateRandNum(int From, int To)
	{
		std::random_device                  Device;
		std::mt19937                        Generator(Device());
		std::uniform_int_distribution<int>    Distr(From, To);

		return Distr(Generator);
	}
}