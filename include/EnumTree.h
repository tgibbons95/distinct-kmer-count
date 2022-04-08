/*****************************************************************//**
 * @file   EnumTree.h
 * @brief  Provides method declarations related to enumerating nodes of a suffix tree
 *
 * @author Thomas Gibbons
 * @date   Apr 2022
 *********************************************************************/

#ifndef ENUM_TREE_H
#define ENUM_TREE_H

namespace CSE_584A
{
   struct Interval
   {
      int start;
      int end;
   };

   struct BiInterval
   {
      Interval forward;
      Interval reverse;
   };

   struct BwtData
   {
      const char* S = nullptr;
      const char* B = nullptr;
      const int* A = nullptr;
      const int* C = nullptr;
      int** Occ = nullptr;
   };

   struct EnumTreeData
   {
      BwtData forward;
      BwtData reverse;
      const char* alphabet = nullptr;
   };

   bool CheckRightDiversity(const EnumTreeData& data, BiInterval I, int d);

   // Stack based.
   void EnumTree(const EnumTreeData& data, BiInterval I, int kLow, int kHigh, int* kmerCount);

   // Recursive based.
   void EnumTree(const EnumTreeData& data, BiInterval I, int d, int kLow, int kHigh, int* kmerCount);
}

#endif