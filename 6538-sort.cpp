#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <string>
#include <pthread.h>
#include <time.h>
#include <algorithm>
#include <pthread.h>
//#define input 20
#define NUMBER_THREADS 2
#define ll long long
const int mod = 1e9 + 7;
const int N = 2e5 + 5;
using namespace std;


const int lengh = 100;
int rarray[lengh];
int input;
vector<int> nums;
int part = 0;
//void readData();


void merge(int low, int mid, int high) {
    int *left = new int[mid - low + 1];
    int *right = new int[high - mid];
    int n1 = mid - low + 1, n2 = high - mid, i, j;
    for (i = 0; i < n1; i++)
        left[i] = nums[i + low];
    for (i = 0; i < n2; i++)
        right[i] = nums[i + mid + 1];
    int k = low;
    i = j = 0;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            nums[k++] = left[i++];
        else
            nums[k++] = right[j++];
    }
    // insert remaining values from left
    while (i < n1) {
        nums[k++] = left[i++];
    }
    // insert remaining values from right
    while (j < n2) {
        nums[k++] = right[j++];
    }
}


void merge_sort(int low, int high) {
    // calculating mid point of array
    int mid = low + (high - low) / 2;
    if (low < high) {
        // calling first half
        merge_sort(low, mid);
        // calling second half
        merge_sort(mid + 1, high);
        // merging the two halves
        merge(low, mid, high);
    }

}

void *merge_sort(void *arg) {
    // which part out of 4 parts
    int MY_THREADS = part++;
    // calculating low and high
    int low = MY_THREADS * (input / 2);
    int high = (MY_THREADS + 1) * (input / 2) - 1;
    // evaluating mid point
    int mid = low + (high - low) / 2;
    if (low < high) {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
    return NULL;
}

void readData() {
    cout << "PLEASE ENTER YOUR INPUTS FILE!!" << endl;
    string filename;
    cin >> filename;
    filename += ".txt";
    string MYFILE = filename;
    ifstream INMYFILE;
    int count = 0;
    string linee;
    string num;
    string array[50];
    string comma;
    int i = 0;
    INMYFILE.open(MYFILE.c_str());
    if (INMYFILE.is_open()) {
        INMYFILE >> input;
        if (input == 0 || input < 0|| isblank(input)) {
            cout << "PLEASE ENTER A VALID NUMBER" << endl;
        } else {
            cout<<"THE UNSORTED ARRAY IS:"<<endl;
            for (int i = 0; i < input; i++) {
                INMYFILE >> rarray[i];
                nums.push_back(rarray[i]);
                cout << nums[i] << " ";

            }
            cout << endl;
            if (nums.size() == input) {
                cout << "the size of the array is :";
                cout << input << endl;
                INMYFILE.close();// CLose input file
            }
        }
    } else { //Error message
        cerr << "Can't find input file " << MYFILE << endl;
    }

    clock_t tic, toc;
    tic = clock();
    pthread_t threads[NUMBER_THREADS];
    if (input != 0 && input > 0 && !isblank(input)) {
        // creating  threads
        for (int i = 0; i < NUMBER_THREADS; i++) {
            pthread_create(&threads[i], NULL, merge_sort, (void *) NULL);
        }

        // joining all threads
        for (int i = 0; i < 2; i++) pthread_join(threads[i], NULL);
        merge(0, (input / 2 - 1) / 2, input / 2 - 1);//feeh hetta malhash lazma 3shan homma mesh kaza thread(aktar men 2) bas nas in case of more threads it would work effeciently
        merge(input / 2, input / 2 + (input - 1 - input / 2) / 2, input - 1);
        merge(0, (input - 1) / 2, input - 1);

        toc = clock();
        cout << "Sorted array: ";
        for (int i = 0; i < input; i++) cout << nums[i] << " ";
        cout<<endl;
        cout << "Time taken: " << (toc - tic) /
                                      (double) CLOCKS_PER_SEC << endl;
        string OUTPUTFILE("output.txt");
        ofstream file_out;
        file_out.open(OUTPUTFILE, std::ios_base::app);
        file_out << "size of the array to sort :" << input << endl;
        file_out << endl;
        file_out << "UNSORTED ARRAY:" << endl;
        for (int i = 0; i < input; i++) {
            file_out << rarray[i] << " "; //the output array

        }
        file_out<<endl;
        file_out<<endl;
        file_out << "SORTED ARRAY:" << endl;
        for (int i = 0; i < input; i++) {
            file_out << nums[i] << " "; //the output array

        }
        file_out << endl;
        file_out << endl;
        file_out << "Time taken: " << (toc - tic) /
                                      (double) CLOCKS_PER_SEC << endl;
        cout << endl;
        time_t timer;
        char buffer[50], line[50]; // puisque j'ai utiliser append to my file each time i haven't creadted a file every time
        struct tm *mytime;      //so i decide to print the time (just have a clean code :)
        time(&timer);
        mytime = localtime(&timer); //it's a built in fuction to get the time by including <time>
        strftime(buffer, 26, "%d-%m-%y %H:%M:%S", mytime); //day-month-year hour:minute:second
        file_out << endl;
        file_out << "THE CALCULATIONS HAS ENDED AT :" << buffer << endl;//just to separate between 2 testing
        cout << endl;
        cout << "YOU HAVE APPEND THE SORTED ARRAY TO THE OUTPUT FILE !" << " ";
    }
}
int main() {
    readData();
    //pthread_t th; //defining the thread
    // pthread_create(&th,NULL,&fi,NULL);//NULL -->pointer to the atribute ex(scheduling or a policy but we don't need it),fuction to execute
    return 0;
}

