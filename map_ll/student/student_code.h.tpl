typedef struct product
{
    char* name;
    double price;
} product_t;

typedef struct node
{
    product_t product;
    struct node* next;
}node_t;

@@prototype@@