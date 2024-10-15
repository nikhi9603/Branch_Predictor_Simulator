#include "bp_simulator.h"

BP_Simulator::BP_Simulator(BP_type bp_type, int m, string traceFileName, int n=0)
{
    this->m = m;
    this->n = n;
    this->bp_type = bp_type;
    trace_file_parser = new TraceFileParser(traceFileName);
}


void BP_Simulator::simulate()
{
    if(bp_type == BIMODAL)
    {
        branch_predictor = new BiModal_BP(m);
    }
    else if(bp_type == GSHARE)
    {
        branch_predictor = new Gshare_BP(m, n);
    }

    while(true)
    {
        pair<bool, TraceEntry> parse_result = trace_file_parser->parseNextInstruction();

        if(parse_result.first == true)      // reached EOF file
        {
            break;
        }
        else
        {
            branch_predictor->predictBranch(parse_result.second);
        }
    }
}


BP_Statistics BP_Simulator::getStatistics()
{
    BP_Statistics bp_stats = branch_predictor->getStatistics();
    bp_stats.branch_mispred_rate = (float) bp_stats.nbranches_mispredict / bp_stats.nbranches;
    return bp_stats;
}



void BP_Simulator::printSimulationOutput()
{
    cout << "OUTPUT" << endl;
    BP_Statistics bp_stats = getStatistics();
    bp_stats.printStats();

    cout << "FINAL ";
    if(bp_type == BIMODAL) 
    {
        cout << "BIMODAL";
    }
    else if(bp_type == GSHARE) 
    {
        cout << "GSHARE";
    }
    cout << " CONTENTS" << endl;

    vector<TwoBitCounter> predCounters = branch_predictor->getPredCounters();

    for(int i = 0; i < predCounters.size(); i++)
    {
        cout << i << " " << predCounters[i].getCounterVal() << endl;
    }
}