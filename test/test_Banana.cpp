// Test
#include "gtest/gtest.h"

#include "BurrowsWheelerTransform.h"
#include "SuffixArray.h"
#include "EnumTree.h"

#include <queue>
#include <iostream>
#include <cstring>

namespace CSE_584A
{
   namespace Testing
   {
      TEST(SuffixArrayTest, Banana)
      {
         const int n = 7;
         char S[n + 1] = "BANANA$";
         int A[n] = {};
         int G[n] = {};
         int expectedA[n] = { 6,5,3,1,0,4,2 };
         int expectedG[n] = { 4,3,6,2,5,1,0 };

         ComputeSuffixArray(S, A, G, n);

         for (int i = 0; i < n; ++i)
         {
            EXPECT_EQ(expectedA[i], A[i]);
            EXPECT_EQ(expectedG[i], G[i]);
         }
      }

      TEST(BurrowsWheelerTransformTest, Banana)
      {
         const int n = 7;
         char S[n + 1] = "BANANA$";
         char B[n + 1] = {};
         int A[n] = { 6,5,3,1,0,4,2 };
         char expectedB[n + 1] = "ANNB$AA";

         ComputeBurrowsWheelerTransform(S, A, B, n);

         for (int i = 0; i < n; ++i)
         {
            EXPECT_EQ(expectedB[i], B[i]);
         }
      }

      TEST(Kmer, Banana)
      {
         const int n = 7;
         char S[n + 1] = "BANANA$";
         char SR[n + 1] = "$ANANAB";
         char B[n + 1] = {};
         char BR[n + 1] = {};
         int G[n] = {};
         int GR[n] = {};
         int A[n] = {};
         int AR[n] = {};
         
         const int alphabetSize = 4;
         const char* alphabet = "$ABN";
         int C[alphabetSize] = {};
         int Occ1[n] = {};
         int Occ2[n] = {};
         int Occ3[n] = {};
         int Occ4[n] = {};
         int* Occ[alphabetSize] = {Occ1, Occ2, Occ3, Occ4 };

         int Cr[alphabetSize] = {};
         int Occr1[n] = {};
         int Occr2[n] = {};
         int Occr3[n] = {};
         int Occr4[n] = {};
         int* Occr[alphabetSize] = { Occr1, Occr2, Occr3, Occr4 };

         ComputeSuffixArray(S, A, G, n);
         ComputeSuffixArray(SR, AR, GR, n);
         ComputeBurrowsWheelerTransform(S, A, B, n);
         ComputeBurrowsWheelerTransform(SR, AR, BR, n);
         ComputeRprev(B, alphabet, C, Occ, n, 1, alphabetSize);
         ComputeRprev(BR, alphabet, Cr, Occr, n, 1, alphabetSize);

         EnumTreeData data;
         data.forward.S = S;
         data.forward.B = B;
         data.forward.C = C;
         data.forward.Occ = Occ;
         data.forward.A = A;
         data.reverse.S = SR;
         data.reverse.B = BR;
         data.reverse.C = Cr;
         data.reverse.Occ = Occr;
         data.reverse.A = AR;
         data.alphabet = alphabet;

         BiInterval I{{0, n - 1},{0,n - 1}};

         const int kLow = 1;
         const int kHigh = 7;
         const int kTotal = kHigh - kLow + 1;
         int kmerCount[kTotal] = {};
         int expectedKmerCount[kTotal] = {3,3,3,3,2,1,0};
         for (int i = kLow; i <= kHigh; ++i)
         {
            kmerCount[i - kLow] = n - i;
         }
         EnumTree(data, I, kLow, kHigh, kmerCount);

         EXPECT_TRUE(std::memcmp(expectedKmerCount, kmerCount, sizeof(kmerCount)) == 0);
      }
   }
}
