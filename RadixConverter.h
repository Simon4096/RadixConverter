#ifndef CXPL_RADIX_CONVERTER
#define CXPL_RADIX_CONVERTER

#include <algorithm>
#include <vector>

namespace cxpl::RadixConverter
{
    template <typename DigitType = int>
    std::vector<DigitType> Convert(std::vector<DigitType> in, int from, int to)
    {
        std::vector<DigitType> out;
        auto BigIntegerMod = [](std::vector<DigitType> &num, int radix, int divisor, DigitType &remainder)
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

        DigitType remainder = 0;
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