#include <iostream>
using namespace std;


int Multiply(int a, int b)
{
    int result = a * b;
    return result;
}

void surprise(){
    int max = 100;
    int min = 2;
    cout << "\n";
    for(int i = min ; i <= max; i++){
        int j = 2;
        while(i%j++ !=0);
        if(j == i+1) cout << "("<< i<<","<<j<<")= " << i <<"\t" << j << endl;

    }
}


void simpson(){
    double eps = 1.0;
    while ((1.0 +eps) > 1.0) {
        eps = eps/2.0;
    }
    eps = eps * 2.0;
    cout.precision(20);
    cout << "eps = " << eps;
}


template <typename T> void sumcum(T* a, T* c, unsigned long n){
    T temp;
    c[0] = a[0];
    for(unsigned long j = 1; j<n ; j ++){
        c[j] = c[j-1]+a[j];
    }
}

void cumulative_sum(){
    unsigned long n =4;
    int* a1 = new int[n];
    a1[0] = 2; a1[1] = 4; a1[2] =5; a1[3] =1;
    int* c1 = new int[n];
    sumcum(a1,c1,n);
    for(unsigned long i =0; i< n ; i++)
    {
        cout << "c1["<<i<<"] = " << c1[i] << endl;
    }
    delete [] a1;
    delete [] c1;
    unsigned long m = 3;
    double* a2 = new double[m];
    a2[0] = 1.3; a2[1] = 2.7; a2[2] = 1.1;
    double* c2 = new double[m];
    sumcum(a2,c2,m);
    for(unsigned long j= 0;j<m;j++){
    cout<< "c2["<< j<< "]="<< c2[j]<< endl;
    }
    delete [] a2;
    delete [] c2;
}
