/*
Approximate Pi using the Leibniz formula
*/

#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

#define NUM_THREADS 2 // adjust this to change the number of threads

#define PAD 8 // prevent false sharing

static long long int num_steps = 1000000000;
double step;

// add synchronization primitive(s) here
mutex sum_mutex;
double pi_shar = 0.0;

// Do not modify this function
inline void single_sum_thread(int id, int num_threads, double sum[NUM_THREADS][PAD])
{
    double x;
    sum[id][0] = 0.0;
    for (long long int i = id; i < num_steps; i = i + num_threads)
    {
        x = (i + 0.5) * step;
        sum[id][0] += 4.0 / (1.0 + x * x);
    }
}

// TODO
inline void pi_sum_thread(int id, double sum_par[NUM_THREADS][PAD])
{
    // add code here
    sum_mutex.lock();
    pi_shar += sum_par[id][0] * step;
    sum_mutex.unlock();
    sleep(1); // DO NOT REMOVE THIS
}
