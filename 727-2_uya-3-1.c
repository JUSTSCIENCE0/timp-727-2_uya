#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *next;
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
    if (l->head==NULL) l->head=new_node;
    else if (l->head->next==NULL) l->head->next = new_node;
    else l->tail->next = new_node;
    l->tail=new_node;
    return 0;
}

int push_front(struct list* l, int val)
{
    struct node* new_node;
    new_node=(struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    if (l->head==NULL)
    {
        new_node->next = NULL;
        l->tail=new_node;
    }   else
        if (l->head->next==NULL) new_node->next = l->tail;
        else new_node->next = l->head;
    l->head=new_node;
    return 0;
}

int insertAfter(struct node* n, int val)
{
    struct node* new_node;
    new_node=(struct node*)malloc(sizeof(struct node));
    new_node->value = val;
    new_node->next = n->next;
    n->next = new_node;
    return 0;
}

int remova(struct list* l, int val)
{
    struct node* tmp1;
    struct node* tmp2;
    tmp1=l->head;
    while(tmp1->value!=val)
    {
        tmp2=tmp1;
        tmp1=tmp1->next;
    }
    if (tmp1==l->head) l->head = tmp1->next;
    else if (tmp1==l->tail)
    {
        tmp2->next=NULL;
        l->tail=tmp2;
    } else tmp2->next = tmp1->next;
    free(tmp1);
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
    print(&a);
    scanf("%d", &x);
    push_front(&a, x);
    print(&a);
    scanf("%d %d", &n, &x);
    b=findk(&a, n);
    insertAfter(b, x);
    print(&a);
    scanf("%d", &x);
    remova(&a, x);
    print(&a);
    clear(&a);
    return 0;
}
