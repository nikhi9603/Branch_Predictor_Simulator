#include "bp_utils.h"
#include<cmath>
#include<iomanip>

// TWO BIT COUNTER
void TwoBitCounter::increment()
{
    if(counter_val != 3)
    {
        counter_val++;
    }
}

void TwoBitCounter::decrement()
{
    if(counter_val != 0)
    {
        counter_val--;
    }
}


// Extract n-bits value starting from index idx in address
long long int getBitsValue(long long int addr, int idx, int n)
{
    long long int mask = ((1ull << n) - 1) << idx ;
    long long int result = (addr & mask) >> idx;
    return result;
}


// BP Statistics
void BP_Statistics::printStats()
{
    cout << " number of predictions:\t" << nbranches << endl;
    cout << " number of mispredictions:\t" << nbranches_mispredict << endl;
    cout << " misprediction rate:\t" << fixed << setprecision(2) << branch_mispred_rate * 100 << "%" << endl;
}


// GLOBAL HISTORY REGISTER
GlobalHistoryRegister::GlobalHistoryRegister(int n)
{
    this->n = n;
    this->register_bits = vector<int>(n, 0);    // GHR initialisation with (0,0,0,...,0)   
}

void GlobalHistoryRegister::pushBit(int newBit)
{
    for(int i = 0; i < n-1; i++)
    {
        register_bits[i] = register_bits[i+1];
    }

    register_bits[n-1] = newBit;
}

long long int GlobalHistoryRegister::getRegisterValue()
{
    long long int register_val = 0;

    for(int i = 0; i < n; i++)
    {
        register_val += (pow(2, i) * register_bits[i]);
    }
    return register_val;
}