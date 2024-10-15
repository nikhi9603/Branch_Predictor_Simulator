#ifndef GSHARE_H
#define GSHARE_H

#include "bp_utils.h"

class Gshare_BP : public Branch_Predictor
{
    private:
        int n_predTableBits;    // m
        int n_ghrBits;          // n

        GlobalHistoryRegister ghr;
    public:
        Gshare_BP(int m, int n);

        void predictBranch(TraceEntry trace_entry) override;
};

#endif