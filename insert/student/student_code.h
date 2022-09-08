typedef struct el item;
struct el{
    int val;
    struct el *next;
};

typedef item *list;

list addToIndex(item *list, int index, item* nouveau);
