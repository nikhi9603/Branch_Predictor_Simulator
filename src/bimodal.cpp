#include "bimodal.h"
#include<cmath>

BiModal_BP::BiModal_BP(int m)
{
    this->n_predTableBits = m;
    this->predCounters = vector<TwoBitCounter>(pow(2, m), TwoBitCounter(2));    // initialise each counter as '2' (weakly taken)
}


void BiModal_BP::predictBranch(TraceEntry trace_entry) 
{
    bp_stats.nbranches++;
    long long int branch_idx = getBitsValue(trace_entry.addr, 2, n_predTableBits);
    int pred_counter_val = predCounters[branch_idx].getCounterVal(); 

    switch (pred_counter_val)
    {
        case 0:     // strongly not taken
        case 1:     // weakly not taken
            if(trace_entry.isBranchTaken_actual)
            {
                bp_stats.nbranches_mispredict++;
                predCounters[branch_idx].increment();
            }
            else
            {
                predCounters[branch_idx].decrement();
            }
            break;
        case 2:     // weakly taken
        case 3:     // strongly taken
            if(trace_entry.isBranchTaken_actual)
            {
                predCounters[branch_idx].increment();
            }
            else
            {
                bp_stats.nbranches_mispredict++;
                predCounters[branch_idx].decrement();
            }
            break;
        default:
            break;
    }
}