#include "gshare.h"
#include<cmath>

Gshare_BP::Gshare_BP(int m, int n)
{
    this->n_predTableBits = m;
    this->n_ghrBits = n;
    this->predCounters = vector<TwoBitCounter>(pow(2, m), TwoBitCounter(2));    // initialise each counter as '2' (weakly taken)
    this->ghr = GlobalHistoryRegister(n_ghrBits);
}


void Gshare_BP::predictBranch(TraceEntry trace_entry)
{
    bp_stats.nbranches++;

    long long int n_pc_bits_val = getBitsValue(trace_entry.addr, 2 + n_predTableBits - n_ghrBits, n_ghrBits);
    long long int pc_xor_ghr = n_pc_bits_val ^ ghr.getRegisterValue();

    long long int temp = getBitsValue(trace_entry.addr, 2, n_predTableBits - n_ghrBits);
    long long int branch_idx = (pc_xor_ghr << (n_predTableBits - n_ghrBits)) | temp;
    int pred_counter_val = predCounters[branch_idx].getCounterVal();

    switch (pred_counter_val)
    {
        case 0:     // strongly not taken
        case 1:     // weakly not taken
            if(trace_entry.isBranchTaken_actual)
            {
                bp_stats.nbranches_mispredict++;
                predCounters[branch_idx].increment();
                ghr.pushBit(1);
            }
            else
            {
                predCounters[branch_idx].decrement();
                ghr.pushBit(0);
            }
            break;
        case 2:     // weakly taken
        case 3:     // strongly taken
            if(trace_entry.isBranchTaken_actual)
            {
                predCounters[branch_idx].increment();
                ghr.pushBit(1);
            }
            else
            {
                bp_stats.nbranches_mispredict++;
                predCounters[branch_idx].decrement();
                ghr.pushBit(0);
            }
            break;
        default:
            break;
    }
}