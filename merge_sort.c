/*-----------------------------------------------------------------------------
Name: Dominic MacIsaac
Course: Operating Systems
Date: September7, 2022
Project: 1 - Recursive Merge Sort on a Linked List
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
int list_len(struct node* head);
struct node* merge(struct node* head1, struct node* head2);
struct node* mergesort(struct node* head, int size);

int main(){
    struct node* head2 = NULL;
    push(&head2, 3);
    push(&head2, 4);
    push(&head2, 2);
    push(&head2, 6);
    push(&head2, 1);
    printf("before:::"); printlist(head2);
    head2 = mergesort(head2, list_len(head2));
    printf("after:::"); printlist(head2);

    struct node* head3 = NULL;
    printf("before:::"); printlist(head3);
    head3 = mergesort(head3, list_len(head3));
    printf("after:::"); printlist(head3);

    struct node* head4 = NULL;
    push(&head4, 1);
    printf("before:::"); printlist(head4);
    head4 = mergesort(head4, list_len(head4));
    printf("after:::"); printlist(head4);

    struct node* head5 = NULL;
    push(&head5, 1);
    push(&head5, 2);
    printf("before:::"); printlist(head5);
    head5 = mergesort(head5, list_len(head5));
    printf("after:::"); printlist(head5);

    struct node* head6 = NULL;
    push(&head6, 1);
    push(&head6, 3);
    push(&head6, 5);
    push(&head6, 2);
    push(&head6, 4);
    push(&head6, 6);

    printf("before:::"); printlist(head6);
    head6 = mergesort(head6, list_len(head6));
    printf("after:::"); printlist(head6);

    return 0;
}

//adds a new node to the start of the list, head is changed to the new node
void push(struct node** head, int new_data){
    struct node* new_node = (struct node*) malloc(sizeof(struct node));
    new_node->data = new_data;
    new_node->next = (*head);
    (*head) = new_node;
    return;
}

//prints linked list with arrows to each next node
void printlist(struct node* head){
    struct node* cur = head;
    while(cur){
        printf("%d->", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

//returns the amount of nodes in a list
int list_len(struct node* head){
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
    struct node* curr = NULL;
    struct node* head = NULL;
    if(left && right){
        if(left->data <= right->data){
            head = left;
            left = left->next;
        }
        else{
            head = right;
            right = right->next;
        }
        curr = head;
    }
    else if(left){
        return left;
    }
    else{
        return right;
    }
    while(left && right){
        if(left->data <= right->data){
            curr->next = left;
            curr = curr->next;
            left = left->next;
        }
        else{
            curr->next = right;
            curr = curr->next;
            right = right->next;
        }
    }
    while(left){
        curr->next = left;
        curr = curr->next;
        left = left->next;
    }
    while(right){
        curr->next = right;
        curr = curr->next;
        right = right->next;
    }
    return head;
}

//recursively descends the list, splitting the nodes and then calling merge to merge them back. Returns the head of the sorted list
struct node* mergesort(struct node* head, int size){
    struct node* left = head;
    struct node* right = head;
    if(size > 1){
        right = right->next;
        for(int i = 0; i < ((size/2)-1); i++){
            left = left->next;
            right = right->next;
        }
        left->next = NULL;
        left = head;
        left = mergesort(left, size/2);
        right = mergesort(right, size-(size/2));
        left = merge(left,right);
    }

    return left;
}
