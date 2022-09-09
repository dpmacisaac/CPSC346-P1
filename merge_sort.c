/*-----------------------------------------------------------------------------
Name: Dominic MacIsaac
Course: Operating Systems
Date: September7, 2022
Project: 1 - Recursive Merge Sort on a Linked List
Implementation:
- Linked List
     - Nodes with integer data and pointer to another struct node
     - reference via a head node
     - Helper functions: push (add node to start of list), 
                         printlist(prints all the data in the nodes in order), 
                         listlen(returns the amount of nodes in the list)
- Merge Sort
     - recursive algorithm that continually calls itself on the left half and right half of the list
     - after descending until there is one node in each list, merge is called on the two sides which 
       place the two lists back together in the sorted order
-----------------------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

//node structure
struct node{
    int data;
    struct node* next;
};

void push(struct node** head, int new_data);
void printlist(struct node* head);
int listlen(struct node* head);
struct node* merge(struct node* head1, struct node* head2);
struct node* mergesort(struct node* head, int size);

int main(){
    
    //empty list test case
    struct node* head3 = NULL;
    printf("empty case:\n");
    printf("before: "); printlist(head3);
    head3 = mergesort(head3, listlen(head3));
    printf("after:  "); printlist(head3);
    printf("\n");

    //one item test case
    struct node* head4 = NULL;
    printf("one item case:\n");
    push(&head4, 1);
    printf("before: "); printlist(head4);
    head4 = mergesort(head4, listlen(head4));
    printf("after:  "); printlist(head4);
    printf("\n");

    //two items test case
    struct node* head5 = NULL;
    printf("two item case:\n");
    push(&head5, 1);
    push(&head5, 2);
    printf("before: "); printlist(head5);
    head5 = mergesort(head5, listlen(head5));
    printf("after:  "); printlist(head5);
    printf("\n");

    //five items test case
    struct node* head2 = NULL;
    printf("five items case:\n");
    push(&head2, 3);
    push(&head2, 4);
    push(&head2, 2);
    push(&head2, 6);
    push(&head2, 1);
    printf("before: "); printlist(head2);
    head2 = mergesort(head2, listlen(head2));
    printf("after:  "); printlist(head2);
    printf("\n");

    //six items test case 
    struct node* head6 = NULL;
    printf("six item case:\n");
    push(&head6, 1);
    push(&head6, 3);
    push(&head6, 5);
    push(&head6, 2);
    push(&head6, 4);
    push(&head6, 6);
    printf("before: "); printlist(head6);
    head6 = mergesort(head6, listlen(head6));
    printf("after:  "); printlist(head6);
    printf("\n");

    return 0;
}

//adds a new node to the start of the list, head is changed to the new node
void push(struct node** head, int new_data){
    struct node* new_node = (struct node*) malloc(sizeof(struct node)); //allocate space for a new node and have new_node point to it
    new_node->data = new_data; //set the data field of the new node to the data from the args
    new_node->next = (*head); //make the new_node's next field point to the head of the list
    (*head) = new_node; //make the head point to the new node
    return;
}

//prints linked list with arrows to each next node
void printlist(struct node* head){
    struct node* cur = head; //pointer to go iterate through the list
    while(cur){ //iterate through til cur is NULL
        printf("%d->", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

//returns the amount of nodes in a list
int listlen(struct node* head){
    struct node* cur = head;
    int counter = 0;
    while(cur){
        counter++;
        cur = cur->next;
    }
    return counter;
}

//helper function for mergesort, merges left and right sides back togther in sorted order
struct node* merge(struct node* head1, struct node* head2){

    
    struct node* left = head1;
    struct node* right = head2;
    struct node* curr = NULL; //for iterating through the list
    struct node* head = NULL; //for holding onto the head of the final list (to be returned)

    //setting the head of the new list
    if(left && right){ //if neither is NULL
        if(left->data <= right->data){ //if left side is smaller than right, set head to the left's first node and move left over one
            head = left;
            left = left->next;
        }
        else{ //vice versa
            head = right;
            right = right->next;
        }
        curr = head; // curr now refers to the head of the list to keep track of adding new nodes to the list
    }
    else if(!right){ // if right is empty, returns left
        return left;
    }
    else{ //if left is empty, returns right
        return right;
    }

    //while both lists still have nodes
    while(left && right){
        if(left->data <= right->data){ //if left is smaller add it to the list and move over one
            curr->next = left;
            curr = curr->next;
            left = left->next;
        }
        else{ //vice versa 
            curr->next = right;
            curr = curr->next;
            right = right->next;
        }
    }
    if(!right){ //if right is empty, put the rest of the left list at the end
        curr->next = left;
    }
    else{ //vice versa
        curr->next = right; 
    }

    return head; //return the head of the new list 
}

//recursively descends the list, splitting the nodes and then calling merge to merge them back. Returns the head of the sorted list
struct node* mergesort(struct node* head, int size){
    //pointers to track the left and right side
    struct node* left = head;
    struct node* right = head;

    //if there are more than 1 items in the list
    if(size > 1){
        right = right->next;
        //iterate through the list, left will point to last item in it's list, right will point to its first item
        for(int i = 0; i < ((size/2)-1); i++){ 
            left = left->next;
            right = right->next;
        }
        left->next = NULL; //break up the left and right sides of the list by removing the connection on the last node of the left side
        left = head; //point the left pointer back to the head of the left list
        left = mergesort(left, size/2); //call merge_sort on the left side
        right = mergesort(right, size-(size/2)); //call merge_sort on the right side
        head = merge(left,right); // merge the left and right sides and set them to the head
    }

    return head; 
}
