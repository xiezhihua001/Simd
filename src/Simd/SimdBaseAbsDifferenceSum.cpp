/*
* Simd Library.
*
* Copyright (c) 2011-2013 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "Simd/SimdMemory.h"
#include "Simd/SimdInit.h"
#include "Simd/SimdExtract.h"
#include "Simd/SimdConst.h"
#include "Simd/SimdMath.h"
#include "Simd/SimdBase.h"

namespace Simd
{
	namespace Base
	{
		void AbsDifferenceSum(const uchar *a, size_t aStride, const uchar *b, size_t bStride, 
			size_t width, size_t height, uint64_t * sum)
		{
			*sum = 0;
			for(size_t row = 0; row < height; ++row)
			{
				int rowSum = 0;
				for(size_t col = 0; col < width; ++col)
				{
					rowSum += AbsDifferenceU8(a[col], b[col]);
				}
				*sum += rowSum;
				a += aStride;
				b += bStride;
			}
		}

		void AbsDifferenceSum(const uchar *a, size_t aStride, const uchar *b, size_t bStride, 
			const uchar *mask, size_t maskStride, uchar index, size_t width, size_t height, uint64_t * sum)
		{
			*sum = 0;
			for(size_t row = 0; row < height; ++row)
			{
				int rowSum = 0;
				for(size_t col = 0; col < width; ++col)
				{
					if(mask[col] == index)
						rowSum += AbsDifferenceU8(a[col], b[col]);
				}
				*sum += rowSum;
				a += aStride;
				b += bStride;
				mask += maskStride;
			}
		}

        void AbsDifferenceSums3x3(const uchar * current, size_t currentStride, const uchar * background, size_t backgroundStride,
            size_t width, size_t height, uint64_t * sums)
        {
            assert(width > 2 && height > 2);

            for(size_t i = 0; i < 9; ++i)
                sums[i] = 0;

            height -= 2;
            width -= 2;
            current += 1 + currentStride;
            background += 1 + backgroundStride;
            for(size_t row = 0; row < height; ++row)
            {
                int rowSums[9];
                for(size_t i = 0; i < 9; ++i)
                    rowSums[i] = 0;

                for(size_t col = 0; col < width; ++col)
                {
                    int value = current[col];
                    rowSums[0] += AbsDifferenceU8(value, background[col - backgroundStride - 1]);
                    rowSums[1] += AbsDifferenceU8(value, background[col - backgroundStride]);
                    rowSums[2] += AbsDifferenceU8(value, background[col - backgroundStride + 1]);
                    rowSums[3] += AbsDifferenceU8(value, background[col - 1]);
                    rowSums[4] += AbsDifferenceU8(value, background[col]);
                    rowSums[5] += AbsDifferenceU8(value, background[col + 1]);
                    rowSums[6] += AbsDifferenceU8(value, background[col + backgroundStride - 1]);
                    rowSums[7] += AbsDifferenceU8(value, background[col + backgroundStride]);
                    rowSums[8] += AbsDifferenceU8(value, background[col + backgroundStride + 1]);
                }

                for(size_t i = 0; i < 9; ++i)
                    sums[i] += rowSums[i];

                current += currentStride;
                background += backgroundStride;
            }
        }

        void AbsDifferenceSums3x3(const uchar *current, size_t currentStride, const uchar *background, size_t backgroundStride,
            const uchar *mask, size_t maskStride, uchar index, size_t width, size_t height, uint64_t * sums)
        {
            assert(width > 2 && height > 2);

            for(size_t i = 0; i < 9; ++i)
                sums[i] = 0;

            height -= 2;
            width -= 2;
            current += 1 + currentStride;
            background += 1 + backgroundStride;
            mask += 1 + maskStride;
            for(size_t row = 0; row < height; ++row)
            {
                int rowSums[9];
                for(size_t i = 0; i < 9; ++i)
                    rowSums[i] = 0;

                for(size_t col = 0; col < width; ++col)
                {
                    if(mask[col] == index)
                    {
                        int value = current[col];
                        rowSums[0] += AbsDifferenceU8(value, background[col - backgroundStride - 1]);
                        rowSums[1] += AbsDifferenceU8(value, background[col - backgroundStride]);
                        rowSums[2] += AbsDifferenceU8(value, background[col - backgroundStride + 1]);
                        rowSums[3] += AbsDifferenceU8(value, background[col - 1]);
                        rowSums[4] += AbsDifferenceU8(value, background[col]);
                        rowSums[5] += AbsDifferenceU8(value, background[col + 1]);
                        rowSums[6] += AbsDifferenceU8(value, background[col + backgroundStride - 1]);
                        rowSums[7] += AbsDifferenceU8(value, background[col + backgroundStride]);
                        rowSums[8] += AbsDifferenceU8(value, background[col + backgroundStride + 1]);
                    }
                }

                for(size_t i = 0; i < 9; ++i)
                    sums[i] += rowSums[i];

                current += currentStride;
                background += backgroundStride;
                mask += maskStride;
            }
        }
	}
}
