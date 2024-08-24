#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int data;
    int ln;
    int rn;
    struct node* left;
    struct node* right;
}node;
node* makePerfect(node* head);
node* createList(int x){
    node* temp = (node*)malloc(sizeof(node));
    temp->data = x;
    temp->ln = 0;
    temp->rn = 0;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node* check(node* head,int x){
    int size = head->ln + head->rn + 1;
    if(size==1){
        return head;
    }
    if(4*(head->ln) > 3*size || 4*(head->rn) > 3*size){
        printf(" reached %d ",x);
        head = makePerfect(head);
        return head;
    }
    if(head->data > x){
        head->left = check(head->left,x);
    }else if(head->data < x){
        head->right = check(head->right,x);
    }
    return head;
}
node* insert(node* head,int x){
    node* temp = head;
    if(temp==NULL){
        temp = createList(x);
        return temp;
    }
    else{
        while(1){
            if(temp->data > x){
                temp->ln += 1;
                if(temp->left==NULL){
                    temp->left = createList(x);
                    break;
                }else{
                    temp = temp->left;
                }
            }else{
                temp->rn +=1;
                if(temp->right==NULL){
                    temp->right = createList(x);
                    break;
                }else{
                    temp = temp->right;
                }
            }
        }
    }
    return check(head,x);
}
void print(node* head){
    node* temp= head;
    if(temp==NULL){
        return;
    }
    printf("%d ",temp->data);
    print(temp->left);
    print(temp->right);
}
int i=0;
void toArray(int arr[],node *head){
    if(head == NULL){
        return;
    }
    toArray(arr,head->left);
    arr[i] = head->data;
    i++;
    toArray(arr,head->right);
}
node* makePerfect(node* head){
    i=0;
    printf(" perfect ");
    int size = head->rn + head->ln +1 ;
    int arr[size+10];
    toArray(arr,head);
    node* root = createList(arr[(size-1)/2]);
    for(int j=0;j<size;j++){
        if(j==(size-1)/2){
            continue;
        }else{
            root = insert(root,arr[j]); 
        }
    }
    return root;
}
int main(){
    node* head = NULL;
    head = insert(head,45);
    head = insert(head,34);
    head = insert(head,54);
    head = insert(head,36);
    head = insert(head,32);
    head = insert(head,56);
    head = insert(head,23);
    head = insert(head,46);
    head = insert(head,22);
    head = insert(head,21);
    head = insert(head,20);
    head = insert(head,19);
    head = insert(head,18);
    // head = makePerfect(head);
    print(head);
    int size = head->ln + head->rn + 1;
    printf("\n%d\n",size);
    return 0;
}