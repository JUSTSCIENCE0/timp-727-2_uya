#include <stdio.h>
#include <stdlib.h>

struct node
{
    int value;
    struct node *parent;
    struct node *left;
    struct node *right;
};

//list

struct nodelist
{
    struct node* adress;
    struct nodelist *next;
};

struct list
{
    struct nodelist	*head;
    struct nodelist *tail;
};

void initlist(struct list* l)
{
    l->head=NULL;
    l->tail=NULL;
}

void clearlist(struct list* l)
{
    struct nodelist* tmp1;
    struct nodelist* tmp2;
    tmp1=l->head;
    while (tmp1->next!=NULL)
    {
        tmp2=tmp1;
        tmp1=tmp1->next;
        free(tmp2);
    }
    free(tmp1);
    initlist(l);
}

int isEmpty(struct list* l)
{
    if (l->head==NULL) return 0;
    else return 1;
}

int	push_back(struct list*	l,	struct node* val)
{
    struct nodelist* new_node;
    new_node=(struct nodelist*)malloc(sizeof(struct nodelist));
    new_node->adress = val;
    new_node->next = NULL;
    if (l->head==NULL) l->head=new_node;
    else if (l->head->next==NULL) l->head->next = new_node;
    else l->tail->next = new_node;
    l->tail=new_node;
    return 0;
}

void printlist(struct list* l)
{
  if (isEmpty(l)==1)
  {
    struct nodelist* tmp;
    tmp=l->head;
    while (tmp->next!=NULL)
    {
        if (tmp->adress == NULL) printf("_ ");
        else
        printf("%d ", tmp->adress->value);
        tmp = tmp->next;
    }
    if (tmp->adress == NULL) printf("_");
    else
    printf("%d", l->tail->adress->value);
  }
}

int NotNULLS(struct list* l)
{
    int r=0;
    if (isEmpty(l)==0) return 0;
    struct nodelist* n;
    n=l->head;
    while (n!=NULL)
    {
        if (n->adress!=NULL) r=1;
        n=n->next;
    }
    return r;
}

int FindNode(struct list* l, struct node* n)
{
    if (l->head==NULL) return 0;
    struct nodelist *tmp;
    tmp=l->head;
    while(tmp->next!=NULL)
    {
        if (tmp->adress==n) return 1;
        else tmp=tmp->next;
    }
    if (l->tail->adress==n) return 1;
    return 0;
}

//tree

struct tree
{
    struct node *root;
    int number;
};

void init(struct tree* t)
{
    t->number=0;
    t->root=NULL;
}

void clear(struct tree *t)
{
    struct list tmp1, tmp2;
    struct nodelist *nd;
    initlist(&tmp1);
    initlist(&tmp2);
    push_back(&tmp1, t->root);
    while(NotNULLS(&tmp1)|| NotNULLS(&tmp2))
    {
        if (isEmpty(&tmp2)==0)
        {
            nd=tmp1.head;
            while(nd!=NULL)
            {
                if (nd->adress==NULL)
                {
                    push_back(&tmp2, NULL);
                    push_back(&tmp2, NULL);
                }
                else
                {
                    push_back(&tmp2, nd->adress->left);
                    push_back(&tmp2, nd->adress->right);
                }
                free(nd->adress);
                nd=nd->next;
            }
            clearlist(&tmp1);
        }
        else
        {
            nd=tmp2.head;
            while(nd!=NULL)
            {
                if (nd->adress==NULL)
                {
                    push_back(&tmp1, NULL);
                    push_back(&tmp1, NULL);
                }
                else
                {
                push_back(&tmp1, nd->adress->left);
                push_back(&tmp1, nd->adress->right);
                }
                free(nd->adress);
                nd=nd->next;
            }
            clearlist(&tmp2);
        }
    }
    init(t);
}

int find(struct tree* t, int val, struct node** n)
{
    struct node* tmp;
    tmp=t->root;
    if (tmp==NULL) return 1;
    while((tmp!=NULL))
    {
        if (tmp->value==val)
        {
            (*n)=tmp;
            return 0;
        }
        if (tmp->value>val)
        {
            if (tmp->left==NULL) return 1;
            else tmp=tmp->left;
        }
        else
        {
            if (tmp->right==NULL) return 1;
            else tmp=tmp->right;
        }
    }
    return 1;
}

int insert(struct tree* t, int val)
{
    struct node* new_node;
    if (find(t, val, &new_node)==0) return 1;
    new_node=(struct node*)malloc(sizeof(struct node));
    if (new_node==NULL) return 2;
    t->number++;
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->value=val;
    if (NULL==t->root)
    {
        new_node->parent=NULL;
        t->root=new_node;
    }
    else
    {
        struct node* tmp;
        int written=0;
        tmp=t->root;
        while (0==written)
        {
            if (val<tmp->value)
            {
                if (tmp->left!=NULL) tmp=tmp->left;
                else
                {
                    new_node->parent=tmp;
                    tmp->left=new_node;
                    written=1;
                }
            }
            else
            {
                if (tmp->right!=NULL) tmp=tmp->right;
                else
                {
                    new_node->parent=tmp;
                    tmp->right=new_node;
                    written=1;
                }
            }
        }
    }
    return 0;
}

void print(struct node* n)
{
    if (n==NULL)
    {
        printf("_\n");
        return;
    }
    struct list tmp1, tmp2;
    struct nodelist *nd;
    initlist(&tmp1);
    initlist(&tmp2);
    push_back(&tmp1, n);
    while(NotNULLS(&tmp1)|| NotNULLS(&tmp2))
    {
        if (isEmpty(&tmp2)==0)
        {
            printlist(&tmp1);
            nd=tmp1.head;
            while(nd!=NULL)
            {
                if (nd->adress==NULL)
                {
                    push_back(&tmp2, NULL);
                    push_back(&tmp2, NULL);
                }
                else
                {
                    push_back(&tmp2, nd->adress->left);
                    push_back(&tmp2, nd->adress->right);
                }
                nd=nd->next;
            }
            clearlist(&tmp1);
        }
        else
        {
            printlist(&tmp2);
            nd=tmp2.head;
            while(nd!=NULL)
            {
                if (nd->adress==NULL)
                {
                    push_back(&tmp1, NULL);
                    push_back(&tmp1, NULL);
                }
                else
                {
                push_back(&tmp1, nd->adress->left);
                push_back(&tmp1, nd->adress->right);
                }
                nd=nd->next;
            }
            clearlist(&tmp2);
        }
    }
}

 void printTree(struct tree *t)
 {
     print(t->root);
 }

 void printDirectly(struct tree *t)
 {
     struct node *n;
     struct list tmp;
     initlist(&tmp);
     int num=0;
     n=t->root;
     while (num!=t->number)
     {
        if (!FindNode(&tmp, n))
        {

            push_back(&tmp, n);
            num++;
            if (n->left!=NULL) n=n->left;
            else
            {
                n=n->parent->right;
                push_back(&tmp, n);
                num++;
                n=t->root;
            }
        }
        else
        {
            n=n->right;
        }
     }
     printlist(&tmp);
 }


int main()
{
    struct tree a;
    int n1, n2, n3, n4, n5, n6, n7;
    scanf("%d %d %d %d %d %d %d", &n1, &n2, &n3, &n4, &n5, &n6, &n7);
    init(&a);
    insert(&a, n1);
    insert(&a, n2);
    insert(&a, n3);
    insert(&a, n4);
    insert(&a, n5);
    insert(&a, n6);
    insert(&a, n7);
    printDirectly(&a);
    printf("\n");
    return 0;
}
