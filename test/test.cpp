#include "stdafx.h"
#include "CppUnitTest.h"

#include "RadixConverter.h"

#include <numeric>
#include <random>
#include <functional>
#include <vector>
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
    TEST_CLASS(RadixConverter)
    {
    public:

        TEST_METHOD(Convert)
        {
            // TODO: Your test code here
            using cxpl::RadixConverter::Convert;

            std::default_random_engine rng;
            std::uniform_int_distribution<int> radix_dist(2, 62);
            auto GetRandomRadix = std::bind(radix_dist, rng);
            std::uniform_int_distribution<int> length_dist(1, 10);
            auto GetRandomLength = std::bind(length_dist, rng);

            for (int n = 0; n < 1000; n++)
            {
                // Generate input
                int radix_from = GetRandomRadix();
                int radix_to = GetRandomRadix();
                int length_from = GetRandomLength();

                std::uniform_int_distribution<int> digit_dist(0, radix_from);
                auto GetRandomDigit = std::bind(digit_dist, rng);

                std::vector<int> in(length_from);
                std::generate(in.begin(), in.end(), GetRandomDigit);

                // Convert
                std::vector<int> out = Convert(in, radix_from, radix_to);

                // Validate
                uint64_t in_value = 0, out_value = 0;
                in_value = std::accumulate(in.begin(), in.end(), in_value, [radix_from](uint64_t value, int digit) {return value * radix_from + digit; });
                out_value = std::accumulate(out.begin(), out.end(), out_value, [radix_to](uint64_t value, int digit) {return value * radix_to + digit; });

                if (in_value != out_value)
                {
                    std::cout << "error" << std::endl;
                    auto out = Convert(in, radix_from, radix_to);
                }

                Assert::AreEqual(in_value, out_value);
            }
        }

    };
}