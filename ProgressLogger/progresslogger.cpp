#include "progresslogger.h"

// -----------------------------------------------------------------------
//           Constructor // Destructor
// -----------------------------------------------------------------------
ProgressLogger::ProgressLogger()
{
    // Cpt init
    progress = new std::atomic<int>(0);
    task_number = new std::atomic<int>(1);
    finished_tasks_cpt = new std::atomic<int>(0);

    // processing flag init
    is_processing = new std::atomic<bool>(false);
}

ProgressLogger::~ProgressLogger(){
}

// -----------------------------------------------------------------------
//           Methods
// -----------------------------------------------------------------------
int ProgressLogger::GetProgress(){
    double d_progress = double(progress->load());
    double d_task_number = double(task_number->load());
    double d_finished_tasks_cpt = double(finished_tasks_cpt->load());
    double current_progress = (100.0 * d_finished_tasks_cpt + d_progress) / (d_task_number);
    return int(current_progress);
}

void ProgressLogger::SetProgress(int p){
    progress->store(p);
}

void ProgressLogger::SetTaskNumber(int n){
    task_number->store(n);
}


void ProgressLogger::MultiplyTaskNumber(int m){
    task_number->store(task_number->load() * m);
}

void ProgressLogger::IncrementFinishedTasksCpt(){
    finished_tasks_cpt->store(finished_tasks_cpt->load() + 1);
    progress->store(0);
}

void ProgressLogger::ResetFinishTasksCpt(){
    finished_tasks_cpt->store(0);
}

bool ProgressLogger::IsProcessing(){
    return is_processing->load();
}

void ProgressLogger::SetIsProcessing(bool b){
    is_processing->store(b);
}

void ProgressLogger::ResetProgressLogger(){
    progress->store(0);
    task_number->store(1);
    finished_tasks_cpt->store(0);
    is_processing->store(false);
}
