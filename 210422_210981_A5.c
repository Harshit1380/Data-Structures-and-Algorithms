#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<limits.h>
typedef long long ll;
ll count = 0;
int partition(int* arr,int l,int r){
    int a=l+1,b=r;
    while(a<b){
        if(arr[a]>arr[l]){
            int temp = arr[a];
            arr[a] = arr[b];
            arr[b] = temp;
            b--;
        }else{
            a++;
        }
    }
    if(arr[a]>arr[l]){
        int temp = arr[a-1];
        arr[a-1] = arr[l];
        arr[l] = temp;
        return a-1;
    }else{
        int temp = arr[a];
        arr[a] = arr[l];
        arr[l] = temp;
        return a;
    }
}
void quicksort(int* arr,int l,int r){
    if(l>=r){
        return;
    }
    int piv = partition(arr,l,r);
    quicksort(arr,l,piv-1);
    quicksort(arr,piv+1,r);
    return;
}
void merge(int arr[],int l,int r){
    int mid = (l+r)/2;
    int p = l;
    int q = mid + 1;
    int size = r - l + 1;
    int arr2[size + 1];
    for(int i=0;i<size;i++){
        arr2[i] = arr[l+i];
    }
    arr2[size] = INT_MAX;
    int i=0;
    while(p != (mid + 1)){
        if(arr2[p-l] > arr2[q-l]){
            arr[i+l] = arr2[q-l];
            q++;
        }
        else{
            arr[i+l] = arr2[p-l];
            p++;
        }
        count++;
        i++;
    }
    return;
}
void mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;
    }
    int mid = (l+r)/2;
    mergeSort(arr,l,mid);
    mergeSort(arr,mid+1,r);
    merge(arr,l ,r);
    return;
}
void impMerge(int arr[],int l,int r){
    int mid = (l+r)/2;
    int p = l;
    int q = mid + 1;
    while(p<=r && q<=r){
        if(arr[p]<arr[q]){
            p++;
        }
        else{
            while(arr[p]>arr[q]){
                int temp;
                temp = arr[p];
                arr[p] = arr[q];
                arr[q] = temp;
                q++;
                p++;
            }
            p++;
        }
    }
}
// void improve_merge(int arr[],int l,int r){
//     int mid = (l+r)/2;
//     int p = l;
//     int q = mid + 1;
//     int size = r - l + 1;
//     int i=0;
//     while(p<=mid && q<size){
//         while(arr[p]>arr[q]){
//             int temp = arr[i];
//             arr[i] = arr[q+i];
//             arr[q+i] = temp;
//             p++;
//             q++;
//         }
//         while()
//     }
// }
// void improve_merge(int arr[],int l,int r){
//     int mid = (l+r)/2;
//     int p = l;
//     int q = mid + 1;
//     int size = r - l + 1;
//     while(p<=mid){
//         while(arr[q]<arr[p]){
//             int temp=arr[q];
//             arr[q] = arr[p];
//             arr[p] = temp;
            
//         }
//     }
// }
void improve_mergeSort(int arr[],int l,int r){
    if(l>=r){
        return;
    }
    int mid = (l+r)/2;
    improve_mergeSort(arr,l,mid);
    improve_mergeSort(arr,mid+1,r);
    if(arr[mid] < arr[mid+1])
        return;
    impMerge(arr,l ,r);
    return;
}
int main(){
    int times = 500;
    int num = times;
    double avg = 0;
    int OutNum = 0;
    while(times--){
        count = 0;
        srand((unsigned)time(NULL));
        clock_t t;
        clock_t time_taken;
        clock_t mEnd;
        int n = 1000000;
        int MAX_RANGE = n;
        int *arr;
        int *arrM;
        arr = (int*)malloc(n*sizeof(int));
        arrM = (int*)malloc(n*sizeof(int));
        for(int i=0;i<n;i++){
            double random_num = ((double)rand()/(double) RAND_MAX)*MAX_RANGE;
            arr[i] = random_num;
            arrM[i] = random_num;
        }
        // double random_num = ((double)rand()/(double) RAND_MAX)*MAX_RANGE;
        t = clock();
        quicksort(arr,0,n-1);
        // printf("\n");
        time_taken = (clock() - t);
        mergeSort(arrM,0,n-1);
        mEnd = (clock() - t - time_taken );
        int time_taken_microsecondsQ = ((double)time_taken * 1000000)/(double)CLOCKS_PER_SEC;
        int time_taken_microsecondsM = ((double)mEnd * 1000000)/(double)CLOCKS_PER_SEC;
        // fclose(fpt);
        avg = (( time_taken_microsecondsM *1.0)/num) + avg;
        if(time_taken_microsecondsM <= time_taken_microsecondsQ)
            OutNum++;
    }
    printf("%lf ", avg);
    printf("%d ",OutNum);
    return 0;
}