#include<stdio.h>
#include<stdlib.h>
typedef struct column{  //linked list for storing the every node of the sparse matrix
    int data;   // Stores value
    int r;  // Stores row number
    int c;  // Stores column number
    struct column* next;    // Links the next node of a row
    struct column* down;    // Links the next node of a column
}column;
typedef struct row{ // Linked list which stores the different rows as data
    column* col;    // Row head of a row
    struct row* next;   // Link to row head of next row
}row;
void print(row* mat){   // Method for printing the sparse matrix, not used in final multiplication
    while(mat!=NULL){   // used 2 loops to traverse the nested linked list data structure made above
        column* colu = mat->col;
        while(colu!=NULL){
            printf("%d ",colu->data);
            colu = colu->next;
        }
        printf("\n");
        mat = mat->next;
    }
}
void connect(row* mat,column* arr[]){   // as the insert method only creates the row links this method is used to create the column links so that the matrix 2 can be traversed easily during multiplication
    while(mat!=NULL){   // traversing the matrix using row links
        column* colu = mat->col;
        while(colu!=NULL){
            if(arr[(colu->c)-1]==NULL){     // Creating links between the column heads and the first nodes of a column
                arr[(colu->c)-1] = colu;
            }else{
                column* t=arr[(colu->c)-1];
                while(t->down!=NULL){   // Storing the lowest node in column for creating links in the bottom most nodes 
                    t=t->down;
                }
                t->down = colu;
            }
            colu = colu->next;
        }
        mat = mat->next;
    }
}
column* colu;
row* insert(row* mat){  // method for inserting nodes in the matrix while creating row links
    if(mat->col==NULL){     // checking if a row has been inserted earlier or not, if not then creating a new row
        mat->col=(column*)malloc(sizeof(column));
        colu = mat->col;
        colu->next=NULL;
        colu->down = NULL;
        scanf("%d %d %d",&(colu->r),&(colu->c),&(colu->data));
    }else{
        int y;
        scanf("%d",&y);
        if(y==colu->r){     // checking if the new node to be created belongs to the same row or a new row has to be created
            colu->next=(column*)malloc(sizeof(column));
            colu = colu->next;
            colu->next=NULL;
            colu->down = NULL;
            scanf("%d %d",&(colu->c),&(colu->data));
            colu->r=y;
        }else{
            mat->next=(row*)malloc(sizeof(row));    // inserting new row as the new element belongs to the new row
            mat=mat->next;
            mat->next=NULL;
            mat->col=(column*)malloc(sizeof(column));
            colu = mat->col;
            colu->r=y;
            scanf("%d %d",&(colu->c),&(colu->data));
        }
    }
    return mat; // returning matrix as it could have been updated while creating new row and having the pointer to bottomost row helps in inserting the further nodes
}
void multiply(row* mat1,row* mat2,column* arr[],int n){
    int f=1;    // flag variable to check whether the output matrix has any non zero elements or not
    while(mat1!=NULL){  // traversing matrix 1 rows
        for(int i=0;i<n;i++){
            column* temp1 = mat1->col;  // creating temporary variables to traverse the matrix
            column* temp2 = arr[i];
            if(temp2==NULL){    // checking if the column has any nodes or not, if not the particular value of output matrix will be 0
                continue;
            }
            int x=0;    // variable for storing the multiplied value of a node of output matrix
            while(temp1!=NULL){     // traversing matrix 1 nodes in a row
                while(temp2!=NULL && (temp2->r)<(temp1->c)){    // going to the node where row number of matrix 2 is equal to column number of matrix 1 as these two values are multiplied during matrix multiplication
                    temp2=temp2->down;
                }
                if(temp2==NULL || temp2->r>temp1->c){   // if row number of matrix 2 becomes greater than the column number of matrix 1 then that means there doesn't exist the node we are searching for
                    temp1=temp1->next;
                }else{      // else node is found and we add the multiplication to the storing variable
                    x+=(temp1->data)*(temp2->data);
                    temp1=temp1->next;
                }
            }
            if(x!=0){   // we only have to print non zero values
                printf("%d %d %d\n",mat1->col->r,i+1,x);
                f=0;    // updating flag variable as an element is present in output matrix
            }
        }
        mat1 = mat1->next;
    }
    if(f){
        printf("NULL MATRIX\n");    // if no element is present ouputting the required output
    }
}
int main(){
    row* matrix1=(row*)malloc(sizeof(row)); // creating the two matrixes and their temporaray copies to traverse the matrix while preserving the head of the both
    row* mat1=matrix1;
    mat1->col=NULL;
    mat1->next=NULL;
    row* matrix2=(row*)malloc(sizeof(row));
    row* mat2=matrix2;
    mat2->col=NULL;
    mat2->next=NULL;
    int n;
    scanf("%d",&n);
    column* arr2[n];    // creating array to store the column head of the second matrix for access of a particular column in O(1) time which makes multiplication efficient
    for(int i=0;i<n;i++){
        arr2[i]=NULL;
    }
    int x=1;
    scanf("%d",&x);
    while(x){   // inserting values while 0 hasn't been encountered 
        if(x==1){   // inserting in the particular matrices
            mat1=insert(mat1);
        }else{
            mat2=insert(mat2);
        }
        scanf("%d",&x);
    }
    mat1=matrix1;   // again storing the matrix heads in the temporary matrices
    mat2=matrix2;
    connect(mat2,arr2); // calling method for creating links in column of matrix 2 only as the matrix 1 only needs to be traversed rowwise
    multiply(mat1,mat2,arr2,n); // calling the multiply method which prints the non zero values of the output matrix;
    return 0;
}