#include<stdio.h>
#include<stdlib.h>
#include"Trie_Graph.h"

int main() {
	Trie *trie = Trie_Create();
	Graph *graph = Graph_Create();
	Graph *mst;

	/* Trie Test */
	Trie_Insert(trie, "pool");
	Trie_Insert(trie, "prize");
	Trie_Insert(trie, "preview");
	Trie_Insert(trie, "prepare");
	Trie_Insert(trie, "produce");
	Trie_Insert(trie, "progress");

	puts("/* In Trie */");
	Trie_Print(trie);
	puts("");

	/* Graph Test */
	Graph_AddVertex(graph, Graph_CreateVertex('A'));
	Graph_AddVertex(graph, Graph_CreateVertex('B'));
	Graph_AddVertex(graph, Graph_CreateVertex('C'));
	Graph_AddVertex(graph, Graph_CreateVertex('D'));
	Graph_AddVertex(graph, Graph_CreateVertex('E'));
	Graph_AddVertex(graph, Graph_CreateVertex('F'));

	Graph_AddArc(graph, 'A', 'B', 6);
	Graph_AddArc(graph, 'A', 'C', 3);
	Graph_AddArc(graph, 'B', 'C', 2);
	Graph_AddArc(graph, 'B', 'D', 5);
	Graph_AddArc(graph, 'C', 'D', 3);
	Graph_AddArc(graph, 'C', 'E', 4);
	Graph_AddArc(graph, 'D', 'E', 2);
	Graph_AddArc(graph, 'D', 'F', 3);
	Graph_AddArc(graph, 'E', 'F', 5);
	
	puts("/* In Graph */");
	Graph_Print(graph);

	puts("\n/* Prim's Algorithm */");
	mst = Graph_CreateMST(graph);
	Graph_Print(mst);

	return 0;
}