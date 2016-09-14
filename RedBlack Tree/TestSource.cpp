#include "Map.h"
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

int main()
{


Map<int, int>* map = new Map<int, int>;
int input = 0;
	int max = 10;
	int s;

	for (input = 1; input <= max; input += 1)
	{

		map->put(s, input);

	}



	delete map;



}