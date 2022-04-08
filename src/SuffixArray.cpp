/*****************************************************************//**
 * @file   SuffixArray.cpp
 * @brief  Provides method implementations related to the suffix array of a string
 *
 * @author Thomas Gibbons
 * @date   Mar 2022
 *********************************************************************/

#include "SuffixArray.h"

#include <algorithm>
#include <queue>

namespace CSE_584A
{
   void ComputeSuffixArray(const char* S, int* A, int* G, int n)
   {
      int* Gp = new (std::nothrow) int[n];
      if (Gp != nullptr)
      {
         // Create initial, unsorted suffix array A from S
         for (int i = 0; i < n; ++i)
         {
            A[i] = i;
         }

         // Sort suffixes in A by first character only.
         auto compareFirstChar = [S](int lhs, int rhs){ return S[lhs] < S[rhs];};
         std::sort(A, A + n, compareFirstChar);

         // Assign group array to index of leftmost entry in A with same 1st char as A[i] while keeping track of groups of more than 1.
         std::queue<std::pair<int, int>> groupIntervals;
         int lastStart = 0;
         for (int i = 0; i < n; ++i)
         {
            G[A[i]] = static_cast<int>(std::lower_bound(A, A + n, A[i], compareFirstChar) - A);
            if (G[A[i]] != G[A[lastStart]])
            {
               if (i - lastStart > 1)
               {
                  groupIntervals.emplace(lastStart, i - 1);
               }
               lastStart = i;
            }
         }
         if (G[A[n - 1]] == G[A[lastStart]] && n - lastStart > 1)
         {
            groupIntervals.emplace(lastStart, n - 1);
         }

         int h = 1;
         while (groupIntervals.size() > 0)
         {
            size_t numGroupIntervals = groupIntervals.size();

            // Iterate through groups
            for (size_t i = 0; i < numGroupIntervals; ++i)
            {
               // Get current interval
               auto groupInterval = groupIntervals.front();
               groupIntervals.pop();

               // Sort the interval
               auto compareGroup = [G, A, h](int lhs, int rhs) 
               { 
                  return G[lhs + h] < G[rhs + h]; 
               };
               std::sort(A + groupInterval.first, A + groupInterval.second + 1, compareGroup);
               lastStart = groupInterval.first;
               for (size_t j = groupInterval.first; j <= groupInterval.second; ++j)
               {
                  Gp[A[j]] = static_cast<int>(std::lower_bound(A + groupInterval.first, A + groupInterval.second + 1, A[j], compareGroup) - A);
                  if (Gp[A[j]] != Gp[A[lastStart]])
                  {
                     if (j - lastStart > 1)
                     {
                        groupIntervals.emplace(lastStart, static_cast<int>(j - 1));
                     }
                     lastStart = j;
                  }
               }
               if (Gp[A[groupInterval.second]] == Gp[A[lastStart]] && groupInterval.second - lastStart > 0)
               {
                  groupIntervals.emplace(lastStart, groupInterval.second);
               }
               for (size_t j = groupInterval.first; j <= groupInterval.second; ++j)
               {
                  G[A[j]] = Gp[A[j]];
               }
            }
            h <<= 1;
         }
         delete[] Gp;
      }
   }
}