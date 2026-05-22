#include "AdjMatGraph.h"
int main()
{
	AdjMatGraph g;

	for (int i=0; i < 4; i++)
	g.insertVertex('A' + i);
	g.insertEdge(0, 1);
	g.insertEdge(0, 3);
	g.insertEdge(1, 2);
	g.insertEdge(1, 3);
	g.insertEdge(2, 3);
	printf("인접 행렬로 표현한그래프\n");
	g.display();

	FILE* fp;
	fopen_s(&fp, "../text_out.txt", "w");
	g.display(fp);
	fclose(fp);

	
	printf("DFS ==> ");
	g.resetVisited();
	g.DFS(0);
	printf("\n");

	return 0;
}