typedef struct Node
{
    char *name;
    char *path;
    
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct Album 
{
    char *name;
    Node *head;
    struct Album *next;
} Album;