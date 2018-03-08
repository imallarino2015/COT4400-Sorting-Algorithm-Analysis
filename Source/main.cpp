/**
*
*   Ian Mallarino
*   z23369342
*   Sorting algorithm running time analysis for insertion sort, merge sort and quicksort.
*
**/
#include<iostream>
#include<fstream>   //for persistent data
#include<chrono>    //calculate elapsed time
#include<random>    //populate the dataset

#include"sort.h"

using namespace std;

void copyArr(int[],int[],int);
void printArr(int[],int,int);
bool isSorted(int[],int);

int main(){
    const int M=10; //number of runs per amount of elements
    const int N_S=5000; //starting number of elements
    const int N_D=5000; //change in number of elements
    const int N_F=100000;   //final number of elements

    int dataLib[M][N_F];

    //populate the array
    ifstream inFile("DataSet.txt");
    if(inFile){
        cout<<"File found. Loading."<<endl;
        //read the data from the file on to the array
        for(int a=0;a<M;a++)
            for(int b=0;b<N_F;b++)
                inFile>>dataLib[a][b];
        cout<<"Finished."<<endl;
        inFile.close();
    }else{
        cout<<"No file found. Generating new file."<<endl;
        inFile.close();
        //generate a new random array
        random_device rand;

        for(int a=0;a<M;a++)
            for(int b=0;b<N_F;b++)
                dataLib[a][b]=rand();
        cout<<"Array generated. Saving to file."<<endl;

        //create a file from the data on the array for later use
        ofstream outFile("DataSet.txt");
        for(int a=0;a<M;a++){
            for(int b=0;b<N_F;b++)
                outFile<<dataLib[a][b]<<"\t";
            outFile<<endl;
        }

        cout<<"Finished saving to file."<<endl;
        outFile.close();
    }

    //setting up
    chrono::steady_clock::time_point iTime;
    chrono::steady_clock::time_point fTime;
    double eTime;
    int currentData[N_F];
    ofstream outFile("Results.txt");
    outFile.setf(ios::fixed);
    outFile.setf(ios::showpoint);
    outFile.precision(7);
    outFile<<"Algorithm"<<"\t"<<"Size"<<"\t";
    for(int run=1;run<=M;run++)
        outFile<<"Run "<<run<<"(s)"<<"\t";
    outFile<<endl;

    //test the algorithms
    //insertion sort
    cout<<"Testing insertion sort."<<endl;
    for(int arrSize=N_S;arrSize<=N_F;arrSize+=N_D){
        outFile<<"Insertion Sort\t"<<arrSize<<"\t";
        for(int run=0;run<M;run++){
            copyArr(dataLib[run],currentData,arrSize);

            iTime=chrono::steady_clock::now();
            insertSort(currentData,arrSize-1);
            fTime=chrono::steady_clock::now();

            eTime=chrono::duration_cast<chrono::duration<double> >(fTime-iTime).count();
            outFile<<eTime<<"\t";
            cout<<"Run "<<run+1<<" completed for insertion sort of "<<arrSize<<" elements. Elapsed time: "<<eTime<<" s."<<endl;
        }
        outFile<<endl;
    }
    outFile<<endl;

    //merge sort
    cout<<"Testing merge sort."<<endl;
    for(int arrSize=N_S;arrSize<=N_F;arrSize+=N_D){
        outFile<<"Merge Sort\t"<<arrSize<<"\t";
        for(int run=0;run<M;run++){
            copyArr(dataLib[run],currentData,arrSize);

            iTime=chrono::steady_clock::now();
            mergeSort(currentData,0,arrSize-1);
            fTime=chrono::steady_clock::now();

            eTime=chrono::duration_cast<chrono::duration<double> >(fTime-iTime).count();
            outFile<<eTime<<"\t";
            cout<<"Run "<<run+1<<" completed for merge sort of "<<arrSize<<" elements. Elapsed time: "<<eTime<<" s."<<endl;
        }
        outFile<<endl;
    }
    outFile<<endl;

    //quicksort
    cout<<"Testing quicksort."<<endl;
    for(int arrSize=N_S;arrSize<=N_F;arrSize+=N_D){
        outFile<<"Quicksort\t"<<arrSize<<"\t";
        for(int run=0;run<M;run++){
            copyArr(dataLib[run],currentData,arrSize);

            iTime=chrono::steady_clock::now();
            quicksort(currentData,0,arrSize-1);
            fTime=chrono::steady_clock::now();

            eTime=chrono::duration_cast<chrono::duration<double> >(fTime-iTime).count();
            outFile<<eTime<<"\t";
            cout<<"Run "<<run+1<<" completed for quicksort of "<<arrSize<<" elements. Elapsed time: "<<eTime<<" s."<<endl;
        }
        outFile<<endl;
    }

    //heap sort
    cout<<"Testing heap sort."<<endl;
    for(int arrSize=N_S;arrSize<=N_F;arrSize+=N_D){
        outFile<<"Heap Sort\t"<<arrSize<<"\t";
        for(int run=0;run<M;run++){
            copyArr(dataLib[run],currentData,arrSize);

            iTime=chrono::steady_clock::now();
            heapSort(currentData,arrSize-1);
            fTime=chrono::steady_clock::now();

            eTime=1000*chrono::duration_cast<chrono::duration<double> >(fTime-iTime).count();
            outFile<<eTime<<"\t";
            cout<<"Run "<<run+1<<" completed for heap sort of "<<arrSize<<" elements. Elapsed time: "<<eTime<<" ms."<<endl;
        }
        outFile<<endl;
    }
    
    return 0;
}

void copyArr(int sourceArr[],int destinationArr[],int length){
    for(int a=0;a<length;a++)
        destinationArr[a]=sourceArr[a];
}

void printArr(int A[],int start,int arrSize){
    for(int a=start;a<arrSize;a++)
        cout<<A[a]<<" ";
    cout<<endl;
}

bool isSorted(int A[],int arrSize){  //checks that the array is sorted
    for(int a=0+1;a<arrSize;a++)
        if(A[a-1]>A[a])
            return false;
    return true;
}
