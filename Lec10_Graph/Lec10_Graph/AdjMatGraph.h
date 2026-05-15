#pragma once
class AdhMatGraph {
protected:
	int size;
	char vertices[MAX_VTXS];
	int adj[MAX_VTXS][MAX_VTXS];
public:
	adjMatGraph() { reset(); }
	char getVertex(int i) { returnvertices[i]; }
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
		if (!isFull()) vertices[size++] = name;
		else printf("Error: 그래프 정점 개수 초과\n");
	}
	void insertEdge(int u, int v) {
		setEdge(u, v, 1);
		setEdge(v, u, 1);
	}
	void display( FILE* fp = stdout ) {
		fprintf(fp, "%c", getVertex(i)); 
		for(int i=0; i<size ; i++){
			fprintf(fp, "%c", getVertex(i));
			for(int j=0; j<size ; j++)
				fprintf(fp, "%3d", getEdge(i, j));
			fprintf(fp, "\n");
	}
	}
};