#ifndef BP_UTILS_H
#define BP_UTILS_H

#include<iostream>
#include<vector>
#include "trace.h"
using namespace std;

class TwoBitCounter
{
    private:
        int counter_val;
    public:
        TwoBitCounter() {counter_val = 0;}
        TwoBitCounter(int initialCounterVal) {counter_val = initialCounterVal;}
    
        void increment();   // when it's 3, it will remain as 3 when incremented
        void decrement();   // when it's 0, it will remain as 0 when decremented

        int getCounterVal()   {return counter_val;}
};

struct BP_Statistics
{
    long long int nbranches = 0;
    long long int nbranches_mispredict = 0;
    float branch_mispred_rate = 0;

    void printStats();
};


/****************************************
 **** BRANCH PREDICTOR GENERAL CLASS ****
****************************************/

class Branch_Predictor      // abstract class
{
    protected:
        vector<TwoBitCounter> predCounters;
        BP_Statistics bp_stats;
    public:
        virtual void predictBranch(TraceEntry trace_entry) = 0;

        BP_Statistics getStatistics() {return bp_stats;}

        vector<TwoBitCounter> getPredCounters() {return predCounters;}
};


/*
 * @brief Gets the int value of address(addr) when 'n' bits taken from starting index 'idx' (inclusive)
 */
long long int getBitsValue(long long int addr, int idx, int n);


class GlobalHistoryRegister
{
    private:
        int n;  // n bits register
        vector<int> register_bits;
    public:
        GlobalHistoryRegister(){}
        GlobalHistoryRegister(int n);

        /*
         * @brief Shifting the GHR to the right by 1 bit, and placing the replace MSB with new bit
         * @param bit bit to be pushed (should be either 0 or 1)
         */
        void pushBit(int newBit); 

        long long int getRegisterValue();
};

#endif
