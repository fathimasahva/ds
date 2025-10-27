//disjoint representation
#include<stdio.h>
#include<stdlib.h>
struct node 
{
int value;
struct rep *repptr; //pointer header node of the list
struct node * next;
};
//structure to represent header node of linked representation of set
struct rep
{
struct node *head;
struct node *tail;
};
//structure to store key & object node pointer 
struct nodaddr
{
int key;
struct node * obj_node_ptr;
struct nodaddr * next;
};
struct nodaddr *ndr=0;//list to store keys & object node pointer
//funtion to create a set for an object 
void makeset(int a)
{ //create an object node pointer
struct nodaddr *t=(struct nodaddr *)malloc(sizeof(struct nodaddr));
//create a new set
struct rep *newset =(struct rep*)malloc(sizeof (struct rep));
struct node *n=(struct node *) malloc(sizeof(struct node));
//fill values
n->value=a;
n->repptr=newset;
n->next=0;
//initialize head & tail
newset->head=newset->tail=n;
//store object node pointer & key
t->obj_node_ptr=n;
t->key=a;
t->next=ndr;
ndr=t;
}
//function to return pointer of the representation (header node) of the set
//containing x
struct rep *find(int X){
struct nodaddr *t=ndr;
while(t!=0 && t->key !=X)
t=t->next;
return t->obj_node_ptr->repptr;}
//to find union of 2 sets corresponding to objects given]

void unionset(int key1,int key2)
{
struct rep *set1,*set2;
struct node *t1;
set1=find(key1);
set2=find(key2);
if(set1==set2)
printf("\n%d and %d belongs to same set \n",key1,key2);
else
{
//changing the header pointer of objects of sets to that set1
t1=set2->head;
while(t1!=0)
{
t1->repptr=set1;
t1=t1->next;
}
set1->tail->next=set2->head;
set1->tail=set2->tail;//set the tail of the set1 to tail of the set2
free(set2);
}
}
//funtion to display a set
void display_set(int a)
{
struct rep *r;
struct node *t;
r=find(a);
t=r->head;
printf("\nset members containing %d:",a);
while(t!=0)
{
printf("%d,",t->value);
t=t->next;
}
}
main()
{
makeset(5);
makeset(10);
makeset(15);
makeset(20);
makeset(25);

printf("\nfind (5)=%X",find(5));
printf("\nfind (10)=%X",find(10));
printf("\nfind (15)=%X",find(15));
printf("\nfind (20)=%X",find(20));
unionset(5,10);
printf("\n after union of 5&10 find(10)=%X",find(10));
unionset(15,20);
printf("\n after union of 15&20 find(20)=%X",find(20));
unionset(10,20);
printf("\n after union of set conataining 10& set conataining 20 find(20)=%X",find(10));
display_set(20);
}

