#include "progresslogger.h"

ProgressLogger::ProgressLogger()
{
    progress = new std::atomic<int>(0);
}

int ProgressLogger::GetProgress(){
    return progress->load();
}

void ProgressLogger::SetProgress(int p){
    progress->store(p);
}
