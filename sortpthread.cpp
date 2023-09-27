// Name Abrham Tamiru
// Class (CECS 325-02)
// Project Name (Prog 3 – Sorting contest)
// Due Date (3/21/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <cstdlib> 
#include <pthread.h>
#include <fstream>
#include <string>

using namespace std;

const int MAX_SIZE = 1000000;
const int thread_size = 8;

struct numbers
{
    int size;
    int arr[MAX_SIZE];
};
numbers num;

void bubbleSort(int* arr, int n)
{
    for ( int i =0; i<n ; i++)
    {
        for (int j=i+1; j<n ;j++)
        {
            if (arr[j]<arr[i])
            {
                swap(arr[i],arr[j]);
            }
        }
    }
}


int* merge(int* arr1, int* arr2, int size_1, int size_2) //merge two arrays 
{
    int* merged = new int[size_1 + size_2];
    int i = 0, j = 0, k = 0;
    while (i < size_1 && j < size_2) 
    {
        if (arr1[i] < arr2[j]) 
        {
            merged[k] = arr1[i];
            i++;
        }
        else 
        {
            merged[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < size_1) 
    {
        merged[k] = arr1[i];
        k++;
        i++;
    }

    while (j < size_2) 
    {
        merged[k] = arr2[j];
        k++;
        j++;
    }

    return merged;
}
void* sort_thread(void* arg) 
{
    int threadNum = *(int*)arg;
    int size = sizeof(num.arr) / sizeof(num.arr[0]);
    int start = threadNum * (size / thread_size);
    int end = (threadNum + 1) * (size / thread_size);
    bubbleSort(&num.arr[start], end - start);
    return NULL;
}
int main(int argc, char* argv[])
{

    if (argc > 3 or argc <3) 
    {
        cout<<"It accepts 2 command line arguments "<<endl;
        cout<< " arg 1: input file"<<endl;
        cout<<" arg 2 : output file"<<endl;
        exit(0);
    }

    // the 2 command line arguments 
    string input_file = argv[1]; 
    string output_file = argv[2];
    
    ifstream infile(argv[1]);
    if(!infile) // check the input file(numbers.dat) is openable
    {
        cout<<"Unable to open the input file"<<endl;
        exit(0);
    }  
    ofstream outfile(argv[2]);
    if (!outfile.is_open()) // check the output file(mysort.out) is openabl
    {
        cout << "Unable to open the output file" << endl;
        exit(0);
    }
  
    int rand_num;
    
    while (infile >> rand_num && num.size<=MAX_SIZE)
    {
        num.arr[num.size]=rand_num;
        num.size++;
    }

    pthread_t threads[thread_size];
    int thread0_num = 0;
    int thread1_num = 1;
    int thread2_num = 2;
    int thread3_num = 3;
    int thread4_num = 4;
    int thread5_num = 5;
    int thread6_num = 6;
    int thread7_num = 7;

    int iret0 = pthread_create(&threads[0], NULL, sort_thread, (void*)&thread0_num);
    int iret1 = pthread_create(&threads[1], NULL, sort_thread, (void*)&thread1_num);
    int iret2 = pthread_create(&threads[2], NULL, sort_thread, (void*)&thread2_num);
    int iret3 = pthread_create(&threads[3], NULL, sort_thread, (void*)&thread3_num);
    int iret4 = pthread_create(&threads[4], NULL, sort_thread, (void*)&thread4_num);
    int iret5 = pthread_create(&threads[5], NULL, sort_thread, (void*)&thread5_num);
    int iret6 = pthread_create(&threads[6], NULL, sort_thread, (void*)&thread6_num);
    int iret7 = pthread_create(&threads[7], NULL, sort_thread, (void*)&thread7_num);
  
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    pthread_join(threads[2], NULL);
    pthread_join(threads[3], NULL);
    pthread_join(threads[4], NULL);
    pthread_join(threads[5], NULL);
    pthread_join(threads[6], NULL);
    pthread_join(threads[7], NULL);

    //merge two threads 
    int *merged1 = merge(&num.arr[0], &num.arr[num.size/8], num.size / 8 , num.size / 8  ); 
    int *merged2 = merge(&num.arr[num.size/8*2], &num.arr[num.size/8*3], num.size / 8 , num.size / 8);
    int *merged3 = merge(&num.arr[num.size /8*4], &num.arr[num.size/8*5], num.size / 8 , num.size / 8);
    int *merged4 = merge(&num.arr[num.size/8*6], &num.arr[ num.size/8*7], num.size / 8 , num.size / 8);
    
    // Merge the two threads from the above 
    int* merged_12 = merge(merged1, merged2, num.size / 4, num.size / 4);
    int* merged_34 = merge(merged3, merged4, num.size / 4, num.size / 4);
    
    int* final_merge = merge(merged_12, merged_34, num.size / 2, num.size / 2);

    for (int i=0 ; i<num.size;i++) 
    {
        outfile <<*final_merge++<< "\n";
    }

    infile.close();
    outfile.close();
    return 0;
}