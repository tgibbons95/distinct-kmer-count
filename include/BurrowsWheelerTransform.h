/*****************************************************************//**
 * @file   BurrowsWheelerTransform.h
 * @brief  Provides method declarations related to the Burrows-Wheeler transform of a string
 *
 * @author Thomas Gibbons
 * @date   Mar 2022
 *********************************************************************/

#ifndef BURROWS_WHEELER_H
#define BURROWS_WHEELER_H

namespace CSE_584A
{
   /**
   * @brief Computes the suffix array for string S.
   * 
   * Using the precomputed suffix array, in linear time the burrows wheeler tranform
   * computes the previous character at each suffix array index.
   *
   * @param[in] S: The string on which to compute the Burrows-Wheeler transform.
   * @param[in] A: The precomputed suffix array of string S.
   * @param[out] B: The Burrows-Wheeler transform of string S.
   * @param[in] n: The length of string S, suffix array A, and Burrows-Wheeler tranform B.
   */
   void ComputeBurrowsWheelerTransform(const char* S, const int* A, char* B, int n);

   void ComputeRprev(const char* S, const char* alphabet, int* C, int** Occ, int n, int k, int alphabetSize);
}

#endif