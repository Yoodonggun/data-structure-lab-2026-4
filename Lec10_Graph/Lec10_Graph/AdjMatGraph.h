#pragma once
#include <stdio.h>
#define	MAX_VTXS	20

class AdjMatGraph {
protected:
	int size;
	char vertices[MAX_VTXS];
	int adj[MAX_VTXS][MAX_VTXS];
public:
	AdjMatGraph() { reset(); }
	char getVertex(int i) { return vertices[i]; }
	int getEdge(int i, int j) { return adj[i][j]; }
	void setEdge(int i, int j, int val) { adj[i][j] = val; }
	bool isEmpty() { return size == 0; }
	bool isFull() { return size >= MAX_VTXS; }
	void reset() {
		size = 0;
		for (int i = 0; i < MAX_VTXS; i++)
			for (int j = 0; j < MAX_VTXS; j++)
				setEdge(i, j, 0);
	}
	void insertVertex(char name) {
		if ( !isFull()) vertices[size++] = name;
		else printf("Error: 그래프 정점 개수 초과\n");
	}
	void insertEdge(int u, int v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1);
	}
	void display( FILE* fp = stdout ) {
		fprintf(fp, "%d", size); 
		for(int i=0; i<size ; i++){
			fprintf(fp, "%c", getVertex(i));
			for(int j=0; j<size ; j++)
				fprintf(fp, "%3d", getEdge(i, j));
			fprintf(fp, "\n");
	}
	}
};


class SrchMGraph : public AdjMatGraph
{
	bool visited[MAX_VTXS];
public:
	void resetVisited() {
		for (int i = 0; i < size; i++)
			visited[i] = false;
	}
	bool isLinked(int u, int v) { return getEdge(u, v) != 0; }

	void DFS(int v) {
		visited[v] = true;
		printf("%c", getVertex(v));

		for (int w = 0; w < size; w++)
			if (isLinked(v, w) && visited[w] == false)
				DFS(w);
	}
};
