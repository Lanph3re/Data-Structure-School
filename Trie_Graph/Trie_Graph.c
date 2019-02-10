#include"Trie_Graph.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

Trie *Trie_Create() {
	Trie *newTrie = (Trie *)malloc(sizeof(Trie));
	
	if (newTrie == NULL) return NULL;

	newTrie->count = 0;
	
	newTrie->root = (TrieNode *)malloc(sizeof(TrieNode));

	if (newTrie->root == NULL) return NULL;

	newTrie->root->isWord = 0;
	for (int i = 0; i < 26; i++)
		newTrie->root->entries[i] = NULL;

	return newTrie;
}

int *_Trie_Insert(TrieNode *root, const char *word) {
	int idx = *word - 'a';

	if (*word == 0) // the end of recursion, which means the end of word
		return 1;

	if (root->entries[idx] == NULL) {
		root->entries[idx] = (TrieNode *)malloc(sizeof(TrieNode));
	
		if (root->entries[idx] == NULL) return NULL;
		
		for (int i = 0; i < 26; i++)
			root->entries[idx]->entries[i] = NULL;
	
		root->entries[idx]->isWord = _Trie_Insert(root->entries[idx], word + 1);
	}
	else {
		_Trie_Insert(root->entries[idx], word + 1);
	}

	return 0;
}

void Trie_Insert(Trie *trie, const char *word) {
	_Trie_Insert(trie->root, word);
	trie->count++;

	return;
}

void _Trie_Print(TrieNode *root) {
	static char arr[100] = "";
	int cur_idx = 0;
	
	if (root->isWord) {
		puts(arr);
		return;
	}

	for (int i = 0; i < 26; i++) {
		if (root->entries[i] != NULL) {
			sprintf(arr, "%s%c", arr, 'a' + i);
			_Trie_Print(root->entries[i]);
			arr[strlen(arr) - 1] = 0;
		}
	}	
}

void Trie_Print(Trie *trie) {
	_Trie_Print(trie->root);
}

Graph *Graph_Create() {
	Graph *newGraph = (Graph *)malloc(sizeof(Graph));

	if (newGraph == NULL) return NULL;

	newGraph->count = 0;
	newGraph->first = NULL;

	return newGraph;
}

Vertex *Graph_GetVertex(Graph *graph, int data) {
	int count = graph->count;
	Vertex *temp = graph->first;

	for (int i = 0; i < count; i++) {
		if (temp->data == data)
			return temp;
		else
			temp = temp->nextVertex;
	}

	return NULL;
}

Vertex *Graph_CreateVertex(int data) {
	Vertex *newVertex = (Vertex *)malloc(sizeof(Vertex));

	if (newVertex == NULL) return NULL;

	newVertex->data = data;
	newVertex->arcList = NULL;
	newVertex->nextVertex = NULL;

	return newVertex;
}

Arc *Graph_CreateArc(Vertex *dest, int weight) {
	Arc *newArc = (Arc *)malloc(sizeof(Arc));

	if (newArc == NULL) return NULL;

	newArc->weight = weight;
	newArc->destination = dest;
	newArc->nextArc = NULL;

	return newArc;
}

void Graph_AddVertex(Graph *graph, Vertex *newVertex) {
	int count = graph->count;
	Vertex *temp = graph->first;

	if (temp == NULL)
		graph->first = newVertex;
	else {
		for (; temp->nextVertex != NULL; temp = temp->nextVertex);

		temp->nextVertex = newVertex;
	}

	graph->count++;
}

void Graph_AddArc(Graph *graph, int src_1, int src_2, int weight) {
	Vertex *src_1_ = Graph_GetVertex(graph, src_1);
	Vertex *src_2_ = Graph_GetVertex(graph, src_2);
	Arc *temp;

	if (!src_1_ || !src_2_)
		return;

	Arc *to_src_1 = Graph_CreateArc(src_1_, weight);
	Arc *to_src_2 = Graph_CreateArc(src_2_, weight);

	temp = src_1_->arcList;
	if (temp == NULL)
		src_1_->arcList = to_src_2;
	else {
		for (; temp->nextArc != NULL; temp = temp->nextArc);

		temp->nextArc = to_src_2;
	}

	temp = src_2_->arcList;
	if (temp == NULL)
		src_2_->arcList = to_src_1;
	else {
		for (; temp->nextArc != NULL; temp = temp->nextArc);

		temp->nextArc = to_src_1;
	}
}

void Graph_Print(Graph *graph) {
	for (Vertex *vertex_temp = graph->first; vertex_temp != NULL; vertex_temp = vertex_temp->nextVertex) {
		printf("%c : ", vertex_temp->data);
		for (Arc *arc_temp = vertex_temp->arcList; arc_temp != NULL; arc_temp = arc_temp->nextArc) {
			printf("--> %c(%d) ", arc_temp->destination->data, arc_temp->weight);
		}
		puts("--> NULL");
	}
}

Graph *Graph_CreateMST(Graph *graph) {
	Graph *MST = Graph_Create();
	Vertex *temp, *temp_, *src_min;
	Arc *arc_temp, *min_arc;
	int **added;
	int is_new, min;
	int added_arc = 0;
	int count = graph->count;

	added = (int **)malloc(sizeof(int *)*(count - 1)); // store arcs that are already chosen in MST.

	if (added == NULL) return NULL;
	
	for (int i = 0; i < count - 1; i++)
		*(added + i) = NULL;

	Graph_AddVertex(MST, Graph_CreateVertex(graph->first->data));
	
	while (added_arc != count-1) { // until the number of added arc in MST is (the number of vertexs - 1)
		temp = MST->first;
		min = 0x7FFFFFFF;

		/* find the arc that has the smallest weight value in greedy way */
		for (temp = MST->first; temp != NULL; temp = temp->nextVertex) {	// temp : Vertex in MST
			temp_ = Graph_GetVertex(graph, temp->data);						// temp_ : Vertex in Graph
			for (arc_temp = temp_->arcList; arc_temp != NULL; arc_temp = arc_temp->nextArc) {
				if (arc_temp->weight < min) {
					is_new = 1;
					for (int **tmp = added; *tmp != NULL; tmp++) {
						if ((*((*tmp)+0) == temp_->data && *((*tmp)+1) == arc_temp->destination->data)|| (*((*tmp) + 0) == arc_temp->destination->data && *((*tmp) + 1) == temp_->data)) // check whether current arc is already chosen in MST.
							is_new = 0;
					}
					if (is_new) {
						min = arc_temp->weight;
						min_arc = arc_temp;		// min_arc : Arc that has smallest weight value so far
						src_min = temp_;		// src_min : Source of min_arc
					}
				}
			}
		}

		if ((*(added + added_arc) = (int*)malloc(sizeof(int) * 2)) == NULL) return NULL; // *(added + added_src) is int[2], which stores two ends of min_arc
		*(*(added + added_arc) + 0) = src_min->data;
		*(*(added + added_arc) + 1) = min_arc->destination->data;

		added_arc++;

		Graph_AddVertex(MST, Graph_CreateVertex(min_arc->destination->data));
		Graph_AddArc(MST, src_min->data, min_arc->destination->data, min_arc->weight);
	}

	return MST;
}