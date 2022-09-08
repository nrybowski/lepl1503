typedef struct Node {
  int value;
  struct Node* next;
} node_l;

int findMinIndex(node_l* LLhead);

int removeTheMinIndex(node_l ** LLhead, int MinIndex);
