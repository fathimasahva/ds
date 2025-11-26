#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct node {
int data;
int status;
struct node *next, *point;
};

int stk[SIZE], sp = 0;

struct node *addvertex(struct node *g, int n) {
struct node *t = (struct node *)malloc(sizeof(struct node));
t->data = n;
t->point = NULL;
t->status = 0;
t->next = g;
g = t;
return g;
}

struct node *find(struct node *g, int n) {
struct node *t = g;
while (t != NULL && t->data != n)
t = t->next;
return t;
}

void addedge(struct node *g, int u, int v) {
struct node *v1 = find(g, u);
struct node *v2 = find(g, v);
if (v1 == NULL || v2 == NULL) return;

struct node *t = (struct node *)malloc(sizeof(struct node));
t->next = v1->point;
v1->point = t;
t->point = v2;
}

void printgraph(struct node *g) {
struct node *t1, *t2, *t3;
printf("\nVertex\tEdge List\n");
t1 = g;
while (t1 != NULL) {
printf("%d \t ", t1->data);
t2 = t1->point;
while (t2 != NULL) {
    t3 = t2->point;
    printf("%d,", t3->data);
    t2 = t2->next;
}
printf("\n");
t1 = t1->next;
}
}

void dfs_visit(struct node *u) {
struct node *t, *t1;
u->status = 1;
t = u->point;
while (t != NULL) {
t1 = t->point;
if (t1->status == 0)
    dfs_visit(t1);
t = t->next;
}
stk[++sp] = u->data;
}

void dfs(struct node *g1) {
struct node *t = g1;
while (t != NULL) {
t->status = 0;
t = t->next;
}

t = g1;
while (t != NULL) {
if (t->status == 0)
    dfs_visit(t);
t = t->next;
}
}

void dfs_visit1(struct node *u) {
struct node *t, *t1;
u->status = 1;
printf("%d ", u->data);
t = u->point;
while (t != NULL) {
t1 = t->point;
if (t1->status == 0)
    dfs_visit1(t1);
t = t->next;
}
}

void dfs1(struct node *g1) {
struct node *t = g1;
while (t != NULL) {
t->status = 0;
t = t->next;
}

while (sp != 0) {
t = find(g1, stk[sp--]);
if (t != NULL && t->status == 0) {
    dfs_visit1(t);
    printf("\n");
}
}
}

struct node *graph_transpose(struct node *g) {
struct node *gt = NULL, *t = g, *t1, *t2;
while (t != NULL) {
gt = addvertex(gt, t->data);
t = t->next;
}

t = g;
while (t != NULL) {
t1 = t->point;
while (t1 != NULL) {
    t2 = t1->point;
    addedge(gt, t2->data, t->data);
    t1 = t1->next;
}
t = t->next;
}
return gt;
}

int main() {
struct node *g = NULL, *gt = NULL;

// Build graph
g = addvertex(g, 8);
g = addvertex(g, 7);
g = addvertex(g, 6);
g = addvertex(g, 5);
g = addvertex(g, 4);
g = addvertex(g, 3);
g = addvertex(g, 2);
g = addvertex(g, 1);
g = addvertex(g, 0);

addedge(g, 1, 2);
addedge(g, 2, 3);
addedge(g, 3, 0);
addedge(g, 2, 4);
addedge(g, 4, 5);
addedge(g, 5, 6);
addedge(g, 6, 4);
addedge(g, 7, 6);
addedge(g, 7, 8);

printf("Original graph:\n");
printgraph(g);

dfs(g); // Fill stack
gt = graph_transpose(g);
printf("\nTranspose graph:\n");
printgraph(gt);

printf("\nStrongly Connected Components:\n");
dfs1(gt);

return 0;
}

