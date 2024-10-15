#ifndef TRACE_H
#define TRACE_H

#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

struct TraceEntry
{
    long long int addr;
    bool isBranchTaken_actual;

    TraceEntry() {}
    TraceEntry(long long int addr, bool isBranchTaken_actual) {this->isBranchTaken_actual = isBranchTaken_actual; this->addr = addr;}
};


class TraceFileParser
{
    private:
        string traceFileName;
        ifstream traceFile;
    public:
        TraceFileParser(string fileName);

        /*
         * @return pair<bool,TraceEntry> bool = true => EOF, bool = false => parsed successfully and returns next trace entry
         */
        pair<bool,TraceEntry> parseNextInstruction();   
};

#endif