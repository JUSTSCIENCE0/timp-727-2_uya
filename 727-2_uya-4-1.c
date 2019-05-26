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
    if (tmp->adress == NULL) printf("_\n");
    else
    printf("%d\n", l->tail->adress->value);
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

int removeNode(struct tree* t, int val)
{
    struct node* tmp;
    if (find(t, val, &tmp)==1) return 1;
    if ((tmp->left==NULL)&&(tmp->right==NULL))
    {
        if (tmp->parent==NULL)
        {
            clear(t);
            return 0;
        }
        if (tmp->parent->left==tmp) tmp->parent->left=NULL;
        else tmp->parent->right=NULL;
        free(tmp);
        t->number--;
        return 0;
    }
    if ((tmp->left==NULL) && (tmp->right!=NULL))
    {
        if (tmp->parent==NULL)
        {
            t->root=tmp->right;
            t->root->parent=NULL;
            free(tmp);
            t->number--;
            return 0;
        }
        if (tmp->parent->left==tmp) tmp->parent->left=tmp->right;
        else tmp->parent->right=tmp->right;
        t->number--;
        free(tmp);
        return 0;
    }
    if ((tmp->right==NULL) && (tmp->left!=NULL))
    {
        if (tmp->parent==NULL)
        {
            t->root=tmp->left;
            t->root->parent=NULL;
            t->number--;
            free(tmp);
            return 0;
        }
        if (tmp->parent->left==tmp) tmp->parent->left=tmp->left;
        else tmp->parent->right=tmp->left;
        t->number--;
        free(tmp);
        return 0;
    }
    if ((tmp->left!=NULL) && (tmp->right!=NULL))
    {
        struct node* min;
        min=tmp->right;
        while(min->left!=NULL)
            min=min->left;
        tmp->value=min->value;

        if (min->right!=NULL)
        {
            if (min->parent->left==min) min->parent->left=min->right;
            else min->parent->right=min->right;
            min->right->parent=min->parent;
        }
        else
        {
            if (min->parent->left==min) min->parent->left=NULL;
            else min->parent->right=NULL;
        }
        t->number--;
        free(min);
        return 0;
    }
}

int removeMin(struct node* n, struct tree* t)
{
    int k;
    while (n->left!=NULL)
        n=n->left;
    k=n->value;
    n->parent->left=NULL;
    if (n->right!=NULL)
        {
            n->parent->left=n->right;
            n->right->parent=n->parent;
        }
    t->number--;
    free(n);
    return k;
}


int rotateRight(struct node *n, struct tree *t)
{
    struct node *tmp;
    if (n->left==NULL) return 1;
    if (n->parent==NULL)
    {
        t->root=n->left;
        n->left->parent=NULL;
    }
    else
    {
        if (n->parent->left==n) n->parent->left=n->left;
        else n->parent->right=n->left;
        n->left->parent=n->parent;
    }
    n->parent=n->left;
    tmp=n->parent->right;
    n->parent->right=n;
    n->left=tmp;
    return 0;
}

int rotateLeft(struct node *n, struct tree *t)
{
    struct node *tmp;
    if (n->right==NULL) return 1;
    if (n->parent==NULL)
    {
        t->root=n->right;
        n->right->parent=NULL;
    }
    else
    {
        if (n->parent->left==n) n->parent->left=n->right;
        else n->parent->right=n->right;
        n->right->parent=n->parent;
    }
    n->parent=n->right;
    tmp=n->parent->left;
    n->parent->left=n;
    n->right=tmp;
    return 0;
}

void print(struct node* n)
{
    if (n==NULL)
    {
        printf("-\n");
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

int main()
{
    struct tree a;
    struct node* b;
    int n, k, m, l;
    init(&a);
    scanf("%d %d %d %d", &n, &k, &m, &l);
    insert(&a, n);
    insert(&a, k);
    insert(&a, m);
    insert(&a, l);
    printTree(&a);
    scanf("%d %d %d", &n, &k, &m);
    insert(&a, n);
    insert(&a, k);
    insert(&a, m);
    printTree(&a);
    scanf("%d", &m);
    k=find(&a, m, &b);
    if (k==1) printf("_\n");
    else
    {
        if (b->parent==NULL) printf("_ ");
        else printf("%d ", b->parent->value);
        if (b->left==NULL) printf("_ ");
        else printf("%d ", b->left->value);
        if (b->right==NULL) printf("_\n");
        else printf("%d\n", b->right->value);
    }
    scanf("%d", &m);
    k=find(&a, m, &b);
    if (k==1) printf("-\n");
    else
    {
        if (b->parent==NULL) printf("_ ");
        else printf("%d ", b->parent->value);
        if (b->left==NULL) printf("_ ");
        else printf("%d ", b->left->value);
        if (b->right==NULL) printf("_\n");
        else printf("%d\n", b->right->value);
    }
    scanf("%d", &m);
    removeNode(&a, m);
    printTree(&a);
    while (rotateLeft(a.root, &a)==0)
        k=0;
    printTree(&a);
    while (rotateRight(a.root, &a)==0)
        k=0;
    printTree(&a);
    printf("%d\n", a.number);
    clear(&a);
    printTree(&a);
    return 0;
}
