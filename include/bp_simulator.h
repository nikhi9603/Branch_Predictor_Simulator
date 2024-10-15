#ifndef BP_SIMULATOR_H
#define BP_SIMULATOR_H

#include<iostream>
#include "trace.h"
#include "bp_utils.h"
#include "bimodal.h"
#include "gshare.h"
using namespace std;

enum BP_type {BIMODAL, GSHARE};

class BP_Simulator
{
    private:
        int m;
        int n;
        TraceFileParser* trace_file_parser;
        
        BP_type bp_type;
        Branch_Predictor* branch_predictor;

        void printCounters();
    public:
        BP_Simulator(BP_type bp_type, int m, string traceFileName, int n);

        void simulate();

        BP_Statistics getStatistics();

        void printSimulationOutput();
};

#endif