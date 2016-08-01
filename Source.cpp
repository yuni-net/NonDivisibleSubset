// https://www.hackerrank.com/challenges/non-divisible-subset

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
#include <string.h>
using namespace std;

int main() {
	// receive input
	int subset_qty, div_value;
	cin >> subset_qty >> div_value;
	if (subset_qty == 1 || div_value == 1)
	{
		cout << "1" << endl;
		return 0;
	}

	int * total_mod = new int[div_value];
	memset(total_mod, 0, sizeof(int)*div_value);
	for (int i = 0; i < subset_qty; ++i)
	{
		int value;
		cin >> value;
		total_mod[value%div_value] += 1;
	}

	// count non-divisible subset
	int total = 0;
	// case: mod = 0
	if (total_mod[0] >= 1)
	{
		total += 1;
	}
	// case: mod = 1,2,...,half-1
	const int half_index = div_value / 2;
	for (int i = 1; i < half_index; ++i)
	{
		int count = total_mod[i];
		if (total_mod[i] < total_mod[div_value - i])
		{
			count = total_mod[div_value - i];
		}
		total += count;
	}
	// case: mod = half
	if ((div_value % 2) == 0)
	{
		total += 1;
	}
	else
	{
		int count = total_mod[half_index];
		if (total_mod[half_index] < total_mod[div_value - half_index])
		{
			count = total_mod[div_value - half_index];
		}
		total += count;
	}

	cout << total << endl;

	delete [] total_mod;

	return 0;
}
