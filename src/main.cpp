#include "bp_simulator.h"

int main(int argc, char* argv[])
{
    int m, n;
    string bp_model, trace_fileName;
    BP_type bp_type;

    if(argc == 4 || argc == 5)
    {
        bp_model = argv[1];

        if(argc == 4 && bp_model == "bimodal")
        {
            m = stoi(argv[2]);
            n = 0;
            trace_fileName = argv[3];
            bp_type = BIMODAL;

            cout << "COMMAND" << endl;
            cout << " " << argv[0] << " " << bp_model << " " << m << " " << trace_fileName << endl;
        }
        else if(argc == 5 && bp_model == "gshare")
        {
            m = stoi(argv[2]);
            n = stoi(argv[3]);
            trace_fileName = argv[4];
            bp_type = GSHARE;

            cout << "COMMAND" << endl;
            cout << " " << argv[0] << " " << bp_model << " " << m << " " << n << " " << trace_fileName << endl;
        }
        else
        {
            cout << "Invalid arguments" << endl;
        }

        BP_Simulator bp_sim = BP_Simulator(bp_type, m, trace_fileName, n);
        bp_sim.simulate();

        bp_sim.printSimulationOutput();    
    }
    else
    {
        cout << "Invalid arguments" << endl;
    }
    return 0;
}