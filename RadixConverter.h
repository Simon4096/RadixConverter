#ifndef CXPL_RADIX_CONVERTER
#define CXPL_RADIX_CONVERTER

#include <algorithm>
#include <vector>

namespace cxpl::RadixConverter
{
	std::vector<int> Convert(std::vector<int> in, int from, int to)
	{
		std::vector<int> out;
		auto BigIntegerMod = [](std::vector<int> &num, int radix, int divisor, int &remainder)
		{
			int divident = 0;
			bool isQuotientNonzero = false;
			for (auto &n : num)
			{
				divident = divident * radix + n;
				n = divident / divisor;
				divident %= divisor;

				isQuotientNonzero = isQuotientNonzero || n > 0;
			}

			remainder = divident;
			return isQuotientNonzero;
		};

		int remainder = 0;
		while (BigIntegerMod(in, from, to, remainder))
		{
			out.push_back(remainder);
		}

		out.push_back(remainder);
		std::reverse(out.begin(), out.end());
		return out;
	}
}


#endif //  CXPL_RADIX_CONVERTER