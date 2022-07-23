/*****************************************************************//**
 * @file   SuffixArray.h
 * @brief  Provides method declarations related to the suffix array of a string
 *
 * @author Thomas Gibbons
 * @date   Mar 2022
 *********************************************************************/

#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

namespace CSE_584A
{   
   /**
   * @brief Computes the suffix array for string S.
   *
   * Using the Manber Myers suffix array construction, the suffix array A is computed 
   * along with a rank array G.
   *
   * @param[in] S: The string on which to compute the suffix array.
   * @param[out] A: The suffix array of string S.
   * @param[out] G: The rank array of string S.
   * @param[in] n: The length of string S, suffix array A, and rank array G.
   */
   void ComputeSuffixArray(const char* S, int* A, int* G, int n);
}

#endif