#include "trace.h"
#define TRACE_DIR_PATH "trace_files/"

TraceFileParser::TraceFileParser(string fileName)
{
    this->traceFileName = fileName;

    string traceFilePath = TRACE_DIR_PATH + traceFileName;
    traceFile.open(traceFilePath);

    if(!traceFile.is_open())
    {
        cerr << "Error in opening file - " << traceFilePath << endl;
    }
}


pair<bool,TraceEntry> TraceFileParser::parseNextInstruction()
{
    TraceEntry branch_instr;
    bool isEOF = false;

    string s1, s2;
    traceFile >> s1 >> s2;

    if(traceFile.fail() && !traceFile.eof())
    {
        cerr << "Invalid input or formatting in trace file 1" << endl;
        exit(EXIT_FAILURE);
    }
    else if(traceFile.eof())
    {
        isEOF = true;
    }
    else if(s2 == "t" || s2 == "n")
    {
        long long int addr = std::stoull(s1, nullptr, 16);
        bool isBranchTaken = (s2 == "t");
        branch_instr = TraceEntry(addr, isBranchTaken);
    }

    return make_pair(isEOF, branch_instr);
}