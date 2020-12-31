#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <unistd.h>
#include "Tree.h"
#include "Tree.cpp"
#include <chrono>
#include <pthread.h>
using namespace std;
using namespace std::chrono;

pthread_t tid1;

int check(int **puzzlee, int num, int k, int l)
{
	bool flag = false;
	int ret = -1;
	
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(((i == k) && (j == l)) && (puzzlee[i][j] != num))
			{
				flag = true;
				
				ret = 0;
			}
			if(puzzlee[i][j] == num)
			{
				flag = true;
				
				ret = 1;
			}
			if(flag == true)
			{
				break;
			}
		}
		if(flag == true)
		{
			break;
		}
	}
	
	return ret;
}
int** PuzzleGenerator()
{
	int num = -1;
	int **puzzle = new int*[4];

	for(int i = 0; i < 4; i++)
	{
		puzzle[i] = new int[4];
	}

	bool flag = false;

	srand(time(NULL));

	for(int m = 0; m < 4; m++)
	{
		for(int n = 0; n < 4; n++)
		{
			puzzle[m][n] = -1;
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			num = rand() % 16 + 1;

			flag = false;

			for(int k = 0; k < 4; k++)
			{
				for(int l = 0; l < 4; l++)
				{
					if((k == i) && (l == j))
					{
						flag = true;
						break;
					}
					if(num == puzzle[k][l])
					{
						int flag = -1;

						do
						{
							num = rand() % 16 + 1;

							flag = check(puzzle, num, k, l);

						} while(flag == 1);
					}
				}

				if(flag == true)
				{
					break;
				}
			}

			puzzle[i][j] = num;
		}
	}

	return puzzle;
}
struct PUZZLE
{
	int **puzzle;
};
void* Thread1(void* arg)
{
	PUZZLE* p = (PUZZLE*)arg;
	
	p->puzzle = PuzzleGenerator();
	
	void* P = (void*)p;
	
	return P;
}
int main(int argc, char* argv[])
{
	auto start = high_resolution_clock::now();
	
	int numofthreads = 0;
	
	numofthreads = atoi(argv[1]);
	
	cout << "Number of Threads : " << numofthreads;
	
	PUZZLE p;
	pthread_create(&tid1, NULL, Thread1, (void*)&p);
	void* P;
	pthread_join(tid1, &P);
	PUZZLE* P1;
	P1 = (PUZZLE*)P;

	P1->puzzle[0][0] = 2;
	P1->puzzle[0][1] = 3;
	P1->puzzle[0][2] = 4;
	P1->puzzle[0][3] = 16;
	P1->puzzle[1][0] = 1;
	P1->puzzle[1][1] = 5;
	P1->puzzle[1][2] = 6;
	P1->puzzle[1][3] = 7;
	P1->puzzle[2][0] = 10;
	P1->puzzle[2][1] = 11;
	P1->puzzle[2][2] = 12;
	P1->puzzle[2][3] = 8;
	P1->puzzle[3][0] = 9;
	P1->puzzle[3][1] = 13;
	P1->puzzle[3][2] = 14;
	P1->puzzle[3][3] = 15;

	/* ----------------- */

	Tree T;

	T.MakeRootNode(P1->puzzle);

	bool flag = false;

	T_Node* current_node = T.getRootNode();
	T_Node* parent_node = T.getRootNode();

	int G = 1;

	while(flag == false)
	{
		cout << "\n\n....................................................";
		
		T.NodePuzzlePrinting(current_node);

		cout << endl << endl;

		T.MakeChildren(current_node, parent_node, T, numofthreads);

		T.FindHeuristicValues(current_node, G, T, numofthreads);

		parent_node = current_node;

		current_node = T.FindPath(current_node, T.getChildrenArray(current_node));

		flag = T.GotGoal(current_node);

		G++;
		
		//sleep(1);
	}

	cout << "\n----------------------Final Result----------------------\n";

	T.NodePuzzlePrinting(current_node);
	
	auto stop = high_resolution_clock::now();
	
	auto duration = duration_cast<microseconds>(stop - start);

	cout << "\n\nA* Running Time : " << duration.count() << " microseconds\n";
}
