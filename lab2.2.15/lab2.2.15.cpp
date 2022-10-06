#include <iostream>
#include <ctime>
#include <thread>
#include <chrono>
#include <algorithm>
#include <stdlib.h>
#include <mutex>
#include <iomanip>
#include <math.h>
using namespace std;
const int input_count = 10000000000;
int min_per_thread = 50000;


double leibniz(int n)
{

    double res = 0;
    for (int i = 0; i < n; ++i)   {
        res += 4.0 * pow(-1, i) / (2.0 * i + 1.0);

        
    }
    return res;
}

void parallel_summ(int count, double* results, int idx) {// ебанистика с ссылкой, поправить
    mutex mtx;
    //mtx.lock();

    int max_threads = (count + min_per_thread - 1) / min_per_thread;
    int hardware_threads = (thread::hardware_concurrency());
    int num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
    cout << "Количество хуйни " << num_threads << '\n';
    int block_size = count / num_threads;



    for (int i = idx; i < num_threads; i += block_size) {


        for (int j = 0; j <block_size; j++)
        {
 
            double num = 0;
            num = 4.0 * pow(-1, j) / (2.0 * j + 1.0);
            results[i] += num;
            //results[i] += num;
            //cout << '\n' << results[i];



        }
        
        //cout << results<<'\n';
    }
    //mtx.unlock();

}


/*long double Pi(long double eps) {
    long double a, rez, b;
    long i = 1;
    b = 4.0;
    a = rez = 4.0;
    while (abs(a) >= eps) {
    b = -b;

    a = b / (2 * i + 1.0);
    i++;
    rez += a;
}
   return rez;
}*/



int main() {
    setlocale(LC_ALL, "Rus");
    //double eps = 1e-7;


    int hardware_threads = std::thread::hardware_concurrency();
    int max_threads = (input_count + min_per_thread - 1) / min_per_thread;
    int num_threads = min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

    double* results = new double[num_threads];
    for (int i = 0; i < num_threads; i++) {
        results[i] = 0;
        //cout << "{E{F{AP{FA{FP{Sa results " << results[i] << '\n';

    }
    thread* threads = new std::thread[num_threads];
    thread::id id;

    double result_itog = 1.0;
    int start1 = clock();
    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; i++) {
        threads[i] = thread(parallel_summ, input_count, ref(results), i);//int count,double results , int idx
    }

    for (int i = 0; i < num_threads; i++) {
        if (threads[i].joinable()) {
            id = threads[i].get_id();
            threads[i].join();

        }
    }
    auto end = chrono::high_resolution_clock::now();
    int end1 = clock();
    double time = (double)(end1 - start1) / CLOCKS_PER_SEC;

    for (int i = 0; i < num_threads; i++)
    {

        cout << "Результат dhtvtyasufdasiodjaspokdkpas" << i << ' ' << results[i] << '\n';
        result_itog = results[i];
    }


    int start2 = clock();
    auto start3 = chrono::high_resolution_clock::now();
    double aboba = leibniz(input_count);
    auto end3 = chrono::high_resolution_clock::now();
    int end2 = clock();
    double time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    delete[] threads;






    cout << "MULTI resultat " << result_itog << '\n';
    cout << "resultat " << aboba << '\n';
    chrono::duration<float> duration = end - start;
    chrono::duration<float> duration1 = end3 - start3;
    cout << '\n' << "Мультити Выполнен за t = " << duration.count() << " seconds" << '\n';
    cout << '\n' << "Выполнен за t = " << duration1.count() << " seconds" << '\n';
    system("pause");
    return 0;

}










/*
int hardware_threads = std::thread::hardware_concurrency();
std::cout << "in this system can be used " << hardware_threads << " threads";

setlocale(LC_ALL, "");
int arr_a[n] = { 0 };
for (int i = 0; i < n; i++) {
    arr_a[i] = rand() % 10;
}
int min_per_thread = 5;
int max_threads = (n + min_per_thread - 1) / min_per_thread;
int num_threads = std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

thread* threads = new std::thread[num_threads];
thread::id id;
int results = 0;

int* arr_results = new int[num_threads];

for (int i = 0; i < num_threads; i++) {
    arr_results[i] = { 0 };
}
cout << '\n';
int start1 = clock();
auto start = chrono::high_resolution_clock::now();
for (int i = 0; i < num_threads; i++) {
    threads[i] = thread(parallel_summ, arr_a, n, ref(arr_results), i);
}

for (int i = 0; i < num_threads; i++) {
    if (threads[i].joinable()) {
        id = threads[i].get_id();

        threads[i].join();

    }
}
delete[] threads;
auto end = chrono::high_resolution_clock::now();
int end1 = clock();
double time = (double)(end1 - start1) / CLOCKS_PER_SEC;
chrono::duration<float> duration = end - start;
int sum_result = 0;
for (int i = 0; i < num_threads; i++)
{
    cout << "Результат" << i << ' ' << arr_results[i] << '\n';
    sum_result += arr_results[i];
}
delete[] arr_results;
cout << "ИТОГИ:" << sum_result << '\n';
cout << '\n' << "Выполнен за t = " << duration.count() << " seconds" << '\n';
cout << '\n' << "Выполнен за 1t = " << time << " seconds" << '\n';

*/



