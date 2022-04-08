/*****************************************************************//**
 * @file   BurrowsWheelerTransform.cpp
 * @brief  Provides method implementations related to the Burrows-Wheeler transform of a string
 *
 * @author Thomas Gibbons
 * @date   Mar 2022
 *********************************************************************/

#include "BurrowsWheelerTransform.h"

#include <vector>
#include <cstring>

namespace CSE_584A
{
   void ComputeBurrowsWheelerTransform(const char* S, const int* A, char* B, int n)
   {
      for (int i = 0; i < n; ++i)
      {
         B[i] = (A[i] == 0) ? S[n - 1] : S[A[i] - 1];
      }
   }

   void ComputeRprev(const char* S, const char* alphabet, int* C, int** Occ, int n, int k, int alphabetSize)
   {
      std::memset(C, 0, sizeof(int) * alphabetSize);
      std::vector<int> currentOccIteration(alphabetSize, 0);
      for (int i = 0; i < n; ++i)
      {
         for (int j = 0; j < alphabetSize; ++j)
         {
            // Iterate C if index is lexicographically smaller.
            if (S[i] < alphabet[j])
            {
               ++C[j];
            }
            // Iterate Occ count up to i.
            else if (S[i] == alphabet[j])
            {
               ++currentOccIteration[j];
            }

            // Save every k-th index in Occ to save space.
            if (i % k == 0)
            {
               Occ[j][i/k] = currentOccIteration[j];
            }
         }
      }
   }
}