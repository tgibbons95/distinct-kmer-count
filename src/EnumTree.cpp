/*****************************************************************//**
 * @file   EnumTree.cpp
 * @brief  Provides method implementations related to enumerating nodes of a suffix tree
 *
 * @author Thomas Gibbons
 * @date   Apr 2022
 *********************************************************************/

#include "EnumTree.h"

#include <algorithm>
#include <list>
#include <stack>
#include <iostream>
#include <cstring>

namespace CSE_584A
{
   struct BiIntervalDepth
   {
      BiInterval I;
      int depth;
      BiIntervalDepth(const BiInterval I, int depth)
         :I(I)
         , depth(depth)
      {

      }
   };

   bool CheckRightDiversity(const EnumTreeData& data, BiInterval I, int d)
   {
      bool diverse = false;
      char a = data.reverse.B[I.reverse.start];
      for (int i = I.reverse.start + 1; i <= I.reverse.end; ++i)
      {
         if (data.reverse.B[i] != a)
         {
            diverse = true;
            break;
         }
      }
      return diverse;
   }

   void EnumTree(const EnumTreeData& data, BiInterval initialI, int kLow, int kHigh, int* kmerCount)
   {
      // Place root node on stack.
      std::stack<BiIntervalDepth> s;
      s.emplace(initialI, 0);
      int alphabetSize = std::strlen(data.alphabet);

      while (s.size() > 0)
      {
         BiInterval I = s.top().I;
         int d = s.top().depth;
         s.pop();

         // Check if this is an internal node.
         if (CheckRightDiversity(data, I, d))
         {
            for (int i = kLow; i <= kHigh; ++i)
            {
               if (d >= i)
               {
                  // Increment one for this internal node.
                  kmerCount[i - kLow] += 1;

                  // Decrement one for every child of this internal node.
                  char a = '!';
                  for (int j = I.forward.start; j <= I.forward.end; ++j)
                  {
                     if (data.forward.S[data.forward.A[j] + d] != a)
                     {
                        a = data.forward.S[data.forward.A[j] + d];
                        kmerCount[i - kLow] -= 1;
                     }
                  }
               }
            }

            std::list<BiInterval> I_prime_list;
            for (int i = 0; i < alphabetSize; ++i)
            {
               BiInterval I_prime;
               I_prime.forward.start = data.forward.C[i] + (I.forward.start > 0 ? data.forward.Occ[i][I.forward.start - 1] : 0);
               I_prime.forward.end = data.forward.C[i] + data.forward.Occ[i][I.forward.end] - 1;

               // Get first and last position in reverse.
               bool startSet = false;
               I_prime.reverse.start = I.reverse.end;
               I_prime.reverse.end = I.reverse.end;
               for (int j = I.reverse.start; j <= I.reverse.end; ++j)
               {
                  if (!startSet && data.reverse.S[data.reverse.A[j] + d] == data.alphabet[i])
                  {
                     startSet = true;
                     I_prime.reverse.start = j;
                  }
                  else if (data.reverse.S[data.reverse.A[j] + d] > data.alphabet[i])
                  {
                     I_prime.reverse.end = j - 1;
                     break;
                  }
               }

               // Prioritize first element to have largest interval.
               if (I_prime_list.size() == 0)
               {
                  I_prime_list.emplace_back(I_prime);
               }
               else if ((I_prime_list.front().forward.end - I_prime_list.front().forward.end) >= (I_prime.forward.end - I_prime.forward.start))
               {
                  I_prime_list.emplace_back(I_prime);
               }
               else
               {
                  I_prime_list.emplace_front(I_prime);
               }
            }

            // Place items on stack from list with first element having largest interval.
            for (auto& I_prime : I_prime_list)
            {
               s.emplace(I_prime, d + 1);
            }
         }
      }

      for (int i = kLow; i <= kHigh; ++i)
      {
         std::cout << i << " " << kmerCount[i - kLow] << std::endl;
      }
   }
}