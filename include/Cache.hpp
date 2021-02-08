//
// Created by vladislav on 29.12.2020.
//

#ifndef TEMPLATE_CACHE_HPP
#define TEMPLATE_CACHE_HPP

#include <iostream>
#include <vector>
#include <string>

class Cache
{
 public:
  Cache(int L1CacheSize, int L3CacheSize);

  void ComplexTest();
  void DisplayingTheExperiment(size_t Number, int Duration);

  int DirectTest(int ArraySize);
  int ReverseTest(int ArraySize);
  int RandomTest(int ArraySize);

  void WarmingUpForDirectTest(int ArraySize, int *Array);
  void WarmingUpForReverseTest(int ArraySize, int *Array);
  void WarmingUpForRandomTest(int ArraySize, int *Array);

  int *ArrayGenerate(int Size);
  void ArrayClearing(int *Array);

  void CountOfExperiments();

  int RandomNumberFromSegment(int Min, int Max);

 private:
  int _L1CacheSize, _L3CacheSize;
  std::vector<int> ArraySizes;

  const int Step = 16;
  const int NumberOfRepetitions = 1000;
  int k = -1;

};

#endif  // TEMPLATE_CACHE_HPP
