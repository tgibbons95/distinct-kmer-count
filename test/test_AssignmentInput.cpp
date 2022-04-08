// Test
#include "gtest/gtest.h"

#include "BurrowsWheelerTransform.h"
#include "SuffixArray.h"
#include "EnumTree.h"

#include <array>
#include <cstring>
#include <iostream>
#include <fstream>
#include <future>
#include <memory>
#include <new>
#include <queue>
#include <thread>

namespace CSE_584A
{
   namespace Testing
   {
      const char* alphabet = "$acgt";
      const int alphabetSize = 5;

      TEST(Assignment, HumanSeq)
      {
         std::ifstream humanSeq("human-seq.txt");
         std::ifstream bwtSeq("testcase.bwt");
         std::ifstream rbwtSeq("testcase.rbwt");

         if (humanSeq.is_open() && bwtSeq.is_open() && rbwtSeq.is_open())
         {
            // Reserve space for the string
            std::string S;
            S.reserve(50000128);
            std::getline(humanSeq, S);
            humanSeq.close();

            // Append additional character
            S.push_back('$');
            int n = S.size();

            // Reserve space for the reverse string
            std::string SR;
            SR.reserve(50000128);
            SR = S;
            std::reverse(SR.begin(), SR.end());

            // Reserve space for the BWT
            std::string actualBwt;
            std::string actualBwtSeparatorLoc;
            actualBwt.reserve(50000128);
            std::getline(bwtSeq, actualBwtSeparatorLoc);
            std::getline(bwtSeq, actualBwt);
            ASSERT_EQ(n, actualBwt.size());

            // Reserve space for the RBWT
            std::string actualRbwt;
            std::string actualRbwtSeparatorLoc;
            actualRbwt.reserve(50000128);
            std::getline(rbwtSeq, actualRbwtSeparatorLoc);
            std::getline(rbwtSeq, actualRbwt);
            ASSERT_EQ(n, actualRbwt.size());

            // Compute Suffix Array on String and Reverse String
            std::unique_ptr<int[]> A(new int[n]);
            std::unique_ptr<int[]> G(new int[n]);
            std::unique_ptr<int[]> AR(new int[n]);
            std::unique_ptr<int[]> GR(new int[n]);
            std::cout << "Started Computing Suffix Array" << std::endl;
            std::thread sa_task1(ComputeSuffixArray, S.c_str(), A.get(), G.get(), n);
            std::thread sa_task2(ComputeSuffixArray, SR.c_str(), AR.get(), GR.get(), n);
            sa_task1.join();
            sa_task2.join();
            std::cout << "Finished Computing Suffix Array" << std::endl;

            // Get rid of unnecessary space
            G.reset();
            GR.reset();

            // Compute Burrows Wheeler Transform on String and Reverse String
            std::unique_ptr<char[]> B(new char[n]);
            std::unique_ptr<char[]> BR(new char[n]);
            std::cout << "Started Computing BWT" << std::endl;
            std::thread bwt_task1(ComputeBurrowsWheelerTransform, S.c_str(), A.get(), B.get(), n);
            std::thread bwt_task2(ComputeBurrowsWheelerTransform, SR.c_str(), AR.get(), BR.get(), n);
            bwt_task1.join();
            bwt_task2.join();
            std::cout << "Finished Computing BWT" << std::endl;

            // Verify they are equal to provide BWT and RBWT
            EXPECT_TRUE(std::memcmp(B.get(), actualBwt.c_str(), n) == 0);
            EXPECT_TRUE(std::memcmp(BR.get(), actualRbwt.c_str(), n) == 0);

            // Initialize C and OCC arrays
            int k = 1;
            std::unique_ptr<int[]> C(new int[n]);
            std::unique_ptr<int[]> CR(new int[n]);
            std::vector<std::unique_ptr<int[]>> OccArrays;
            std::vector<int*> Occ;
            std::vector<int*> OccR;
            for (int i = 0; i < 2 * alphabetSize; ++i)
            {
               OccArrays.emplace_back(std::move(std::unique_ptr<int[]>(new int[n / k])));
            }

            for (int i = 0; i < alphabetSize; ++i)
            {
               Occ.emplace_back(OccArrays[2 * i].get());
               OccR.emplace_back(OccArrays[2 * i + 1].get());
            }

            // Compute Rprev arrays C and OCC on BWT and RBWT
            std::cout << "Started Computing Rprev" << std::endl;
            std::thread rprev_task1(ComputeRprev, B.get(), alphabet, C.get(), Occ.data(), n, k, alphabetSize);
            std::thread rprev_task2(ComputeRprev, BR.get(), alphabet, CR.get(), OccR.data(), n, k, alphabetSize);
            rprev_task1.join();
            rprev_task2.join();
            std::cout << "Finished Computing Rprev" << std::endl;

            EXPECT_TRUE(std::memcmp(C.get(), CR.get(), alphabetSize) == 0);

            EnumTreeData data;
            data.forward.S = S.c_str();
            data.forward.B = B.get();
            data.forward.C = C.get();
            data.forward.Occ = Occ.data();
            data.forward.A = A.get();
            data.reverse.S = SR.c_str();
            data.reverse.B = BR.get();
            data.reverse.C = CR.get();
            data.reverse.Occ = OccR.data();
            data.reverse.A = AR.get();
            data.alphabet = alphabet;

            BiInterval I{ {0, n - 1},{0,n - 1} };

            const int kLow = 20;
            const int kHigh = 40;
            const int kTotal = kHigh - kLow + 1;
            int kmerCount[kTotal] = {};
            for (int i = kLow; i <= kHigh; ++i)
            {
               kmerCount[i - kLow] = n - i;
            }
            std::cout << "Started Computing Kmers" << std::endl;
            EnumTree(data, I, kLow, kHigh, kmerCount);
            std::cout << "Finished Computing Kmers" << std::endl;
         }
         else
         {
            std::cout << "Did not run on human-seq.txt" << std::endl;
         }
      }
   }
}
