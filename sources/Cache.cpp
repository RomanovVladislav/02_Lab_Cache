//
// Created by vladislav on 29.12.2020.
//

#include <Cache.hpp>
#include <iostream>
#include <chrono>

Cache::Cache(int L1CacheSize, int L3CacheSize)
{
  _L1CacheSize = L1CacheSize;
  _L3CacheSize = L3CacheSize;
  CountOfExperiments();
}

void Cache::ComplexTest()
{
  std::cout << "investigation:" << std::endl
            << "  travel_variant: direct" << std::endl
            << "  experiments:" << std::endl;

  for (size_t i = 0; i < ArraySizes.size(); ++i)
  {
    DisplayingTheExperiment(i, DirectTest(ArraySizes[i]));
  }

  std::cout << "investigation:" << std::endl
            << "  travel_variant: reverse" << std::endl
            << "  experiments:" << std::endl;

  for (size_t i = 0; i < ArraySizes.size(); ++i)
  {
    DisplayingTheExperiment(i, ReverseTest(ArraySizes[i]));
  }

  std::cout << "investigation:" << std::endl
            << "  travel_variant: random" << std::endl
            << "  experiments:" << std::endl;

  for (size_t i = 0; i < ArraySizes.size(); ++i)
  {
    DisplayingTheExperiment(i, RandomTest(ArraySizes[i]));
  }
}

void Cache::DisplayingTheExperiment(size_t Number, int Duration)
{
    std::cout << "- experiment:" << std::endl
              << "    number: " << Number + 1 << std::endl
              << "    input data:" << std::endl
              << "      buffer_size: " << ArraySizes[Number] / 256 << " KiB" << std::endl
              << "    results:" << std::endl
              << "      duration: " << Duration << "mcs" << std::endl;
}

int Cache::DirectTest(int ArraySize)
{
  int *Array = ArrayGenerate(ArraySize);
  WarmingUpForDirectTest(ArraySize, Array);

  int Time = 0;

  for (int j = 0; j < NumberOfRepetitions; ++j)
  {
    auto StartTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < ArraySize; i += Step)
    {
      k = Array[i];
    }

    auto FinishTime = std::chrono::high_resolution_clock::now();
    Time += std::chrono::duration_cast<std::chrono::microseconds>(FinishTime - StartTime).count();
  }
  Time/=NumberOfRepetitions;

  ArrayClearing(Array);

  return Time;
}

int Cache::ReverseTest(int ArraySize)
{
  int *Array = ArrayGenerate(ArraySize);
  WarmingUpForReverseTest(ArraySize, Array);

  int Time = 0;

  for (int j = 0; j < NumberOfRepetitions; ++j)
  {
    auto StartTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < ArraySize; i += Step)
    {
      k = Array[ArraySize - i - 1];
    }

    auto FinishTime = std::chrono::high_resolution_clock::now();
    Time += std::chrono::duration_cast<std::chrono::microseconds>(FinishTime - StartTime).count();
  }
  Time/=NumberOfRepetitions;

  ArrayClearing(Array);

  return Time;
}

int Cache::RandomTest(int ArraySize)
{
  int *Array = ArrayGenerate(ArraySize);
  WarmingUpForRandomTest(ArraySize, Array);

  int Time = 0;

  for (int j = 0; j < NumberOfRepetitions; ++j)
  {
    auto StartTime = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < ArraySize; i += Step)
    {
      k = Array[RandomNumberFromSegment(0, ArraySize - 1)];
    }

    auto FinishTime = std::chrono::high_resolution_clock::now();
    Time += std::chrono::duration_cast<std::chrono::microseconds>(FinishTime - StartTime).count();
  }
  Time/=NumberOfRepetitions;

  ArrayClearing(Array);

  return Time;
}

void Cache::WarmingUpForDirectTest(int ArraySize, int *Array)
{
  for (int i = 0; i < ArraySize; i += Step)
  {
    k = Array[i];
  }
}

void Cache::WarmingUpForReverseTest(int ArraySize, int *Array)
{
  for (int i = 0; i < ArraySize; i += Step)
  {
    k = Array[ArraySize - i - 1];
  }
}

void Cache::WarmingUpForRandomTest(int ArraySize, int *Array)
{
  for (int i = 0; i < ArraySize; i += Step)
  {
    k = Array[RandomNumberFromSegment(0, ArraySize - 1)];
  }
}

int* Cache::ArrayGenerate(int Size)
{
  int *Array = new int[Size];

  for (int i = 0;i < Size; ++i)
  {
    Array[i] = random();
  }

  return Array;
}

void Cache::ArrayClearing(int *Array)
{
  delete[] Array;
}

void Cache::CountOfExperiments()
{
  int CurrentSize = 0;
  CurrentSize = _L1CacheSize/2;

  while (CurrentSize < 3/2 * _L3CacheSize)
  {
    ArraySizes.push_back(CurrentSize * 256);
    CurrentSize*=2;
  }

  ArraySizes.push_back(3 * _L3CacheSize/2 * 256);
}

int Cache::RandomNumberFromSegment(int Min, int Max)
{
  int RandomNumber = Min + random() % (Max - Min +1);
  return RandomNumber;
}