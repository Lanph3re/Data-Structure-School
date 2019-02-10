#pragma once
/* Trie ADT */
typedef struct TrieNode {
	struct TrieNode *entries[26];
	int isWord;
} TrieNode;

typedef struct {
	int count;
	struct TrieNode *root;
} Trie;

Trie *Trie_Create();
int *_Trie_Insert(TrieNode *root, char *word);
void Trie_Insert(Trie *trie, char *word);
void _Trie_Print(TrieNode *root);
void Trie_Print(Trie *trie);


/* Graph ADT */
typedef struct vertex {
	int data;
	struct vertex *nextVertex;
	struct arc_{
		int weight;
		struct vertex *destination;
		struct arc_ *nextArc;
	} *arcList;
} Vertex;

typedef struct arc {
	int weight;
	struct vertex *destination;
	struct arc *nextArc;
} Arc;

typedef struct graph{
	int count; // the number of Vertexs in Graph;
	Vertex *first;
} Graph;



Graph *Graph_Create();
Vertex *Graph_GetVertex(Graph *graph, int data);
Vertex *Graph_CreateVertex(int data);
Arc *Graph_CreateArc(Vertex *dest, int weight);
void Graph_AddVertex(Graph *graph, Vertex *newVertex);
void Graph_AddArc(Graph *graph, int src_1, int src_2, int weight);
void Graph_Print(Graph *graph);
Graph *Graph_CreateMST(Graph *graph);