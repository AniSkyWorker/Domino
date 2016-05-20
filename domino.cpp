// Аникин О. ПС-21 ДОМИНО Лабораторная работа №1

#include "stdafx.h"
#include <fstream>
#include <iostream>

const int MAX = 20;
const int SET = 7;

struct Domino
{
	int dominoCount;
	int currentPath[MAX * 2];
	int endOfCurrentPath;
	int bestPath[MAX * 2];
	int maxLenOfPath;
	bool endOfBacktracking;
	int bones[SET][SET];

	Domino()
		:endOfBacktracking(false)
		, dominoCount(0)
		, currentPath()
		, bestPath()
		, endOfCurrentPath(0)
		, maxLenOfPath(0)
	{
		for (int i = 0; i < SET; i++)
		{
			for (int j = 0; j < SET; j++)
			{
				bones[i][j] = 0;
			}
		}

		Initialization();
	}

	void Initialization()
	{
		std::ifstream input("input.txt");

		input >> dominoCount;
		int first, second;

		for (int i = 0; i < dominoCount; i++)
		{
			input >> first >> second;
			bones[first][second]++;
			bones[second][first]++;
		}
	}

	void FindMaxPath()
	{
		for (int domino = 0; domino < SET; domino++)
			CreatePath(domino);
	}

	void CreatePath(int first)
	{
		if (endOfBacktracking)
		{
			return;
		}
		for (int second = 0; second < SET; second++)
		{
			if (bones[first][second] > 0)
			{
				bones[first][second]--;
				bones[second][first]--;
				currentPath[endOfCurrentPath] = first;
				currentPath[endOfCurrentPath + 1] = second;
				endOfCurrentPath += 2;
				if (HasContinue(second))
				{
					CreatePath(second);
				}
				else
				{
					CheckPathLen();
				}
				endOfCurrentPath -= 2;
				bones[first][second]++;
				bones[second][first]++;
			}
		}
	}

	bool HasContinue(int first)
	{
		for (int second = 0; second < SET; second++)
		{
			if (bones[first][second] > 0)
			{
				return true;
			}
		}
		return false;
	}


	void CheckPathLen()
	{
		if (endOfCurrentPath > maxLenOfPath)
		{
			bool zeroPath = true;
			for (int i = 0; i < endOfCurrentPath; i++)
			{
				if (currentPath[i] != 0)
				{
					zeroPath = false;
					continue;
				}
			}

			if (zeroPath)
				return;

			for (int i = 0; i < endOfCurrentPath; i++)
			{
				bestPath[i] = currentPath[i];
			}

			maxLenOfPath = endOfCurrentPath;
		}

		else if (endOfCurrentPath == maxLenOfPath)
		{
			for (int i = 0; i < endOfCurrentPath; i++)
			{
				if (bestPath[i] < currentPath[i])
				{
					for (int i = 0; i < endOfCurrentPath; i++)
					{
						bestPath[i] = currentPath[i];
					}
					break;
				}
			}
		}

		endOfBacktracking = (maxLenOfPath % 2 == dominoCount);
	}

	void WriteMaxPathInFile()
	{
		std::ofstream output("output.txt");
		for (int i = 0; i < maxLenOfPath; i++)
		{
			output << bestPath[i];
		}

	}
};

int main()
{
	Domino domino;

	domino.FindMaxPath();
	domino.WriteMaxPathInFile();

	return 0;
}

