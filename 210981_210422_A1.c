#include<stdio.h>
#include<time.h>
void power(long long int n,int arr[2][2]){
    if(n==1){
        arr[0][0]=1;
        arr[0][1]=1;
        arr[1][0]=1;
        arr[1][1]=0;
        return;
    }
    if(n%2==0){
        int arr1[][2]={1,1,1,0};
        power(n/2,arr1);
        arr[0][0] = (arr1[0][0]*arr1[0][0]+arr1[0][1]*arr1[1][0])%2021;
        arr[0][1] = (arr1[0][0]*arr1[0][1]+arr1[0][1]*arr1[1][1])%2021;
        arr[1][0] = (arr1[1][0]*arr1[0][0]+arr1[1][1]*arr1[1][0])%2021;
        arr[1][1] = (arr1[1][0]*arr1[0][1]+arr1[1][1]*arr1[1][1])%2021;
    }else{
        int arr1[][2]={1,1,1,0};
        power(n/2,arr1);
        arr[0][0] = (arr1[0][0]*arr1[0][0]+arr1[0][1]*arr1[1][0]+arr1[0][0]*arr1[0][1]+arr1[0][1]*arr1[1][1])%2021;
        arr[0][1] = (arr1[0][0]*arr1[0][0]+arr1[0][1]*arr1[1][0])%2021;
        arr[1][0] = (arr1[1][0]*arr1[0][0]+arr1[1][1]*arr1[1][0]+arr1[1][0]*arr1[0][1]+arr1[1][1]*arr1[1][1])%2021;
        arr[1][1] = (arr1[1][0]*arr1[0][0]+arr1[1][1]*arr1[1][0])%2021;
    }
}
int rfib(long long int n){
    if(n==0){
        return 0;
    }else if(n==1){
        return 1;
    }
    return (rfib(n-1) + rfib(n-2))%2021;
}
int IFib(long long int n){
    int fab;
    int a=0,b=1;
    fab = b;
    if(n==0){
        fab=a;
    }else{
        for(int i=0;i<n;i++){
            int temp = b;
            fab=(temp+a)%2021;
            b=fab;
            a=temp;
        }
    }
    return fab;
}
int main(){
    long long int n;
    scanf("%lld",&n);
    // long long int t=100000;                  // For CleverFib
    // int sol[2][2] = {{1,1},{1,0}};           // For CleverFib
    clock_t start , end;
    double total;
    start = clock();
    // for(int i=0;i<t;i++){                    // For CleverFib
    //     power(n-1,sol);                      // For CleverFib
    // }                                        // For CleverFib
    // printf("%d\n",sol[0][0]);                // For CleverFib
    // printf("%d\n",rfib(n));                  // For RFib
    // printf("%d\n",IFib(n));                  // For IFib
    end = clock();
    total = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken : %f",total);
    return 0;
}