#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <fstream>
#include <string>
#include <pthread.h>
#include <time.h>
#include <sstream>
#include <iomanip>
#define MAX_THREAD 4
#define ll long long
const int mod = 1e9 + 7;
const int N = 2e5 + 5;
using namespace std;
int x, y, x2, y2;
const int m = 2000;
const int n = 2000;
int rmatrix[m][n];
int rmatrix2[m][n];
int result[m][n];
int result2[m];
int step_i = 0;
int cthread = 0;
int cthread2 = 0;
vector<int> row[m];
vector<int> col[n];
int result3[m][n];

void *MULTI_ROW(void *arg) { //pass row
    int i = *((int *) arg);
    for (int j = 0; j < y2; j++) { //column
        //result[i][j] = 0;
        for (int k = 0; k < x2; k++) {
            result[i][j] += rmatrix[i][k] * rmatrix2[k][j];
        }

    }
    cthread++;
    return NULL;
}


void *mult_element(void *arg) {
    int *data = (int *) arg; //2a5adt el struct elly feeha eldata elly heya elelemats
    int k = 0,
    i = 0;
    int x = data[0];
    for (i = 1; i <= x; i++){
        k += data[i] * data[i + x];
    } //the multiplication of the matrix 3ady
    int *p = (int *) malloc(4000*sizeof(int)); //hana5od multiplication elly 3amlnalha store in k and we will pass it to p elly hanerga3 beeha
    *p = k;
    //Used to terminate a thread and the return value is passed as a pointer
    cthread2++;
    pthread_exit(p);
    free(p);
    return NULL;
}
void *element(void *data) {
    int i, j;
    sscanf((char *) data, "%d %d", &i, &j);
    int len, na, nb;
    na = row[i].size();
    nb = col[j].size();
    if (na > nb) {
        len = nb;
    } else {
        len = na;
    }
    int sum = 0;
    for (int k = 0; k < len; k++)
        sum += row[i][k] * col[j][k];
    result3[i][j] = sum;
    return NULL;
}


void readData() {
    cout << "PLEASE ENTER YOUR INPUTS FILE!!" << endl;
    string filename;
    cin >> filename;
    filename += ".txt"; //user doesn't need to put .txt
    string MYFILE = filename;
    //string MYFILE = "mymatrix.txt"; //ha2ra esm el file lessa
    ifstream INMYFILE;
    istringstream sin;
    string line;
    INMYFILE.open(MYFILE.c_str());
    if (INMYFILE.is_open()) {
        INMYFILE >> x >> y;
        getline(INMYFILE, filename);
        istringstream sin(filename);
        if (sin.eof()) cerr << "\nError no more data"; //mesh sha8ala lazem a3edha
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                INMYFILE >> rmatrix[i][j];
            }
        }
    }
    INMYFILE >> x2 >> y2;
    for (int i = 0; i < x2; i++) {
        for (int j = 0; j < y2; j++) {
            INMYFILE >> rmatrix2[i][j];
        }
    }
    if (x != 0 && y != 0 && x2 != 0 && y2 != 0) {
        cout << "SIZE OF THE FIRST MATRIX IS:" << x << "x" << y;
        for (int i = 0; i < x; i++) {
            cout << endl;
            for (int j = 0; j < y; j++) {
                cout << rmatrix[i][j] << " ";
            }
        }
        cout << endl;
        cout << endl;
        cout << "SIZE OF THE SECOND MATRIX IS:" << x2 << "x" << y2;
        for (int i = 0; i < x2; i++) {
            cout << endl;
            for (int j = 0; j < y2; j++) {
                cout << rmatrix2[i][j] << " ";
            }
        }
        cout << endl << endl;
        if (y == x2) {
            cout << "YOU CAN MULTIPLY YOUR MATICES EASILY WITH THE MINIMUM COST ;) " << endl;
        } else {
            cout << "OOOPS!!YOU CAN't MULTIPLY THE 2 MATRICES,GO AND REVISE YOUR MATHS COURSES FIRST :(" << endl;
        }
    } else {
        cout << "PLEASE ENTER THE SIZE OF YOU MATRIX" << endl;
    }
    cout << endl;
 clock_t t1, t2, t3, t4;
  if (y == x2) {
        t1 = clock();
        pthread_t threads[y];//max_thread =number of rows
        int p[x];  //we make an array to save the thread and to point to it
        for (int i = 0; i < x; i++) {
            p[i] = i;
            pthread_create(&threads[i], NULL, MULTI_ROW, &p[i]);// p argument elly ana ba3ataha
        }

        for (int i = 0; i < x; i++){
         pthread_join(threads[i], NULL);
         }
        t2 = clock();
        cout << endl
             << "Multiplication of MATRIX 1 and MATRIX 2 OF SIZE EQUALS:" << x << "x" << y2 << endl;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y2; j++)
                cout << result[i][j] << " ";
            cout << endl;
        }
        cout << endl;
        cout << "THE NUMBER OF THREADS IN THIS ATTEMPT EQUALS:" << cthread;
        cout << endl;
        cout << "Time taken for The computation of each row of the output matrix happens in a thread is : " << (t2 - t1)
                                                                                                               /
                                                                                                               (double) CLOCKS_PER_SEC
             << endl;
             int size = x * y2;
        pthread_t *threads2;
        threads2 = (pthread_t *) malloc(size * sizeof(pthread_t));
        int count = 0;
        int *resultant = NULL;
        int buffer[4000];
        for(int i=0;i<x;i++)/*malhash lazma*/
            for(int j=0;j<y;j++)
                row[i].push_back(rmatrix[i][j]);
        for(int i=0;i<x;i++)
            for(int j=0;j<y;j++)
                row[i].push_back(rmatrix2[i][j]);/*malhash lazma*/

        //3amla 2 for loops 3shan wahda llcolumns w wahda llrows f hayeb2a lkol resultant thread
             t3 = clock();
        for (int i = 0; i < x; i++)
            for (int j = 0; j < y2; j++) {
                //storing row and column elements in resultant
                //i created struct to pass more than one argument
                resultant = (int *) malloc((2000) * sizeof(int));
                resultant[0] = y;
                for (int k = 0; k < y; k++) //storing each element of matrix 1
                    resultant[k + 1] = rmatrix[i][k];
                for (int k = 0; k < x2; k++)//storing with each element of matrix2
                    resultant[k + y + 1] = rmatrix2[k][j];
                //creating threads
                sprintf(reinterpret_cast<char *>(buffer), "%d %d", i, j);//for sending it to fumction elements bas bazet menny
                pthread_create(&threads2[count++], NULL, mult_element, (void *) (resultant));
               // free(resultant);

            }
        cout << endl;
        cout << endl
             << "Multiplication of MATRIX 1 and MATRIX 2 OF SIZE EQUALS:" << x << "x" << y2 << endl;
        for (int i = 0; i < size; i++) {
            void *k;
            //Joining all threads and collecting return value
            pthread_join(threads2[i], &k);
            int *p2 = (int *) k;
            result2[i] = *p2;
        }
        t4 = clock();
        for (int i = 0; i < size; i++) {
            cout << result2[i] << " ";
            if ((i + 1) % y2 == 0)
                cout << "\n";
        }

        cout << endl;
        cout << "THE NUMBER OF THREADS IN THIS ATTEMPT EQUALS:" << cthread2;
        cout << endl;
        cout << "Time taken for The computation of each resultant of the output matrix happens in a thread : "
             << (t4 - t3) / (double) CLOCKS_PER_SEC
             << endl;
              string OUTPUTFILE("output2.txt");
        ofstream file_out;
        file_out.open(OUTPUTFILE, std::ios_base::app);
        if (y = x2) {
            file_out << "Multiplication of MATRIX 1 and MATRIX 2 OF SIZE EQUALS:" << x << "x" << y2 << endl;
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y2; j++)
                    file_out << result[i][j] << " ";
                file_out << endl;
            }
            file_out << endl;
            file_out << "THE NUMBER OF THREADS IN THIS ATTEMPT EQUALS:" << cthread;
            file_out << endl;
            file_out << "Time taken for The computation of each row of the output matrix happens in a thread is : "
                     << (t2 - t1)
                        /
                        (double) CLOCKS_PER_SEC
                     << endl;
            file_out << endl
                     << "Multiplication of MATRIX 1 and MATRIX 2 OF SIZE EQUALS:" << x << "x" << y2 << endl;
            for (int i = 0; i < size; i++) {
                file_out << result2[i] << " ";
                if ((i + 1) % y2 == 0) file_out << '\n';
            }
            file_out << endl;
            file_out << "THE NUMBER OF THREADS IN THIS ATTEMPT EQUALS:" << cthread2;
            file_out << endl;
            file_out << "Time taken for The computation of each resultant of the output matrix happens in a thread : "
                     << (t4 - t3) / (double) CLOCKS_PER_SEC
                     << endl;
            time_t timer;
            char buffer[26], line[50]; // puisque j'ai utiliser append to my file each time i haven't creadted a file every time
            struct tm *mytime;      //so i decide to print the time (just have a clean code :)
            time(&timer);
            mytime = localtime(&timer); //it's a built in fuction to get the time by including <time>
            strftime(buffer, 26, "%d-%m-%y %H:%M:%S", mytime); //day-month-year hour:minute:second
            file_out << endl;
            file_out << "THE CALCULATIONS HAS ENDED AT :" << buffer << endl;//just to separate between 2 testing
            cout << endl;
            cout << "YOU HAVE APPEND THE 2 MULTIPLIED MATICES TO THE OUTPUT2 FILE !" << " ";

        }
    } else {
        string OUTPUTFILE("output2.txt");
        ofstream file_out;
        file_out.open(OUTPUTFILE, std::ios_base::app);
        file_out << endl;
        file_out << "OOOPS!!YOU CAN't MULTIPLY THE 2 MATRICES,GO AND REVISE YOUR MATHS COURSES FIRST :(" << endl;
        file_out << endl;

             }
    
}

int main() {
    readData();
    return 0;
}

