#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *next;
    struct node *prev;
};

struct list
{
    struct node	*head;
    struct node *tail;
};

void init(struct list* l)
{
    l->head=NULL;
    l->tail=NULL;
}

void clear(struct list* l)
{
    struct node* tmp1;
    struct node* tmp2;
    tmp1=l->head;
    while (tmp1->next!=NULL)
    {
        tmp2=tmp1;
        tmp1=tmp1->next;
        free(tmp2);
    }
    free(tmp1);
    init(l);
}
int isEmpty(struct list* l)
{
    if (l->head==NULL) return 0;
    else return 1;
}

struct node* find(struct list* l, int val)
{
    struct node* tmp;
    tmp=l->head;
    while (tmp->next!=NULL)
    {
        if (tmp->value==val) return tmp;
        tmp=tmp->next;
    }
    return NULL;
}

struct node* findk(struct list* l, int n)
{
    int i=1;
    struct node* tmp;
    tmp=l->head;
    for(i=1; i<n; i++) tmp=tmp->next;
    return tmp;
}

int	push_back(struct list*	l,	int	val)
{
    struct node* new_node;
    new_node=(struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    new_node->next = NULL;
    if (l->head==NULL)
    {
        new_node->prev = NULL;
        l->head=new_node;
    }
    else if (l->head->next==NULL)
    {
        new_node->prev = l->head;
        l->head->next = new_node;
    }
    else
    {
        new_node->prev = l->tail;
        l->tail->next = new_node;
    }
    l->tail=new_node;
    return 0;
}

int push_front(struct list* l, int val)
{
    struct node* new_node;
    new_node=(struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    new_node->prev = NULL;
    if (l->head==NULL)
    {
        new_node->next = NULL;
        l->tail=new_node;
    }   else if (l->head->next==NULL)
    {
        new_node->next = l->tail;
        l->tail->prev = new_node;
    }
        else
        {
            new_node->next = l->head;
            l->head->prev = new_node;
        }
    l->head=new_node;
    return 0;
}

int insertAfter(struct node* n, int val)
{
    struct node* new_node;
    new_node=(struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    new_node->next = n->next;
    new_node->prev = n;
    n->next->prev = new_node;
    n->next = new_node;
    return 0;
}

int insertBefore(struct node* n, int val)
{
    struct node* new_node;
    new_node=(struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    new_node->prev = n->prev;
    new_node->next = n;
    n->prev->next = new_node;
    n->prev = new_node;
    return 0;
}

int removeFirst(struct list* l, int val)
{
    struct node* tmp;
    tmp=l->head;
    while(tmp->value!=val) tmp=tmp->next;
    if (tmp==l->head)
    {
        tmp->next->prev = NULL;
        l->head = tmp->next;
    }
    else if (tmp==l->tail)
    {
        tmp->prev->next = NULL;
        l->tail = tmp->prev;
    } else
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    free(tmp);
    return 0;
}

int removeLast(struct list* l, int val)
{
    struct node* tmp;
    tmp=l->tail;
    while(tmp->value!=val) tmp=tmp->prev;
    if (tmp==l->head)
    {
        tmp->next->prev = NULL;
        l->head = tmp->next;
    }
    else if (tmp==l->tail)
    {
        tmp->prev->next = NULL;
        l->tail = tmp->prev;
    } else
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    free(tmp);
    return 0;
}

void print(struct list* l)
{
  if (isEmpty(l)==1)
  {
    struct node* tmp;
    tmp=l->head;
    while (tmp->next!=NULL)
    {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("%d\n", l->tail->value);
  }
}

void print_invers(struct list* l)
{
  if (isEmpty(l)==1)
  {
    struct node* tmp;
    tmp=l->tail;
    while (tmp->prev!=NULL)
    {
        printf("%d ", tmp->value);
        tmp = tmp->prev;
    }
    printf("%d\n", l->head->value);
  }
}

int main()
{
    int n, x, i, k1, k2, k3;
    struct list a;
    struct node* b;
    init(&a);
    scanf("%d", &n);
    for (i=1; i<=n; i=i+1)
    {
        scanf("%d", &x);
        push_back(&a, x);
    }
    print(&a);
    scanf("%d %d %d", &k1, &k2, &k3);
    b=find(&a, k1);
    if (b!=NULL) k1=1; else k1=0;
    b=find(&a, k2);
    if (b!=NULL) k2=1; else k2=0;
    b=find(&a, k3);
    if (b!=NULL) k3=1; else k3=0;
    printf("%d%d%d\n", k1, k2, k3);
    scanf("%d", &x);
    push_back(&a, x);
    print_invers(&a);
    scanf("%d", &x);
    push_front(&a, x);
    print(&a);
    scanf("%d %d", &n, &x);
    b=findk(&a, n);
    insertAfter(b, x);
    print_invers(&a);
    scanf("%d %d", &n, &x);
    b=findk(&a, n);
    insertBefore(b, x);
    print(&a);
    scanf("%d", &x);
    removeFirst(&a, x);
    print_invers(&a);
    scanf("%d", &x);
    removeLast(&a, x);
    print(&a);
    clear(&a);
    return 0;
}
