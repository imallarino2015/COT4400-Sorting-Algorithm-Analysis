#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include<limits>    //sentinel for merge function

///Algorithm 1: Insertion sort
void insertSort(int A[],int n){
    for(int j=1;j<=n;j++){
        int key=A[j];
        int i=j-1;
        while(i>=0 && A[i]>key){
            A[i+1]=A[i];
            i--;
        }
        A[i+1]=key;
    }
}

///Algorithm 2: Merge sort
void merge(int A[],int p,int q,int r){
    int n1=q-p+1;
    int n2=r-q;

    int* L=new int[n1+1];
    int* R=new int[n2+1];

    for(int i=0;i<n1;i++)
        L[i]=A[p+i];
    for(int j=0;j<n2;j++)
        R[j]=A[q+j+1];

    L[n1]=std::numeric_limits<int>::max();
    R[n2]=std::numeric_limits<int>::max();
    int i=0;
    int j=0;

    for(int k=p;k<=r;k++)
        if(L[i]<=R[j]){
            A[k]=L[i];
            i++;
        }else{
            A[k]=R[j];
            j++;
        }

    delete[] L;
    delete[] R;
}

void mergeSort(int A[],int p,int r){
    if(p<r){
        int q=(p+r)/2;
        mergeSort(A,p,q);
        mergeSort(A,q+1,r);
        merge(A,p,q,r);
    }
}

///Algorithm 3: Quicksort
void exchange(int& val1,int& val2){
    int temp=val1;
    val1=val2;
    val2=temp;
}

int partition(int A[],int p,int r){
    int x=A[r];
    int i=p-1;
    for(int j=p;j<=r-1;j++)
        if(A[j]<=x){
            i++;
            exchange(A[i],A[j]);
        }
    exchange(A[i+1],A[r]);
    return i+1;
}

void quicksort(int A[],int p,int r){
    if(p<r){
        int q=partition(A,p,r);
        quicksort(A,p,q-1);
        quicksort(A,q+1,r);
    }
}

#endif // SORT_H_INCLUDED
