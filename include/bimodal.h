#ifndef BIMODAL_H
#define BIMODAL_H

#include "bp_utils.h"

class BiModal_BP : public Branch_Predictor
{
    private:
        int n_predTableBits;    // m
    public:
        BiModal_BP(int m);

        void predictBranch(TraceEntry trace_entry) override;
};

#endif