#ifndef PROGRESSLOGGER_H
#define PROGRESSLOGGER_H

#include <iostream>
#include <atomic>

/*
        The purpose of this class is to communicate the progress status of
    a working thread to the ui thread. It uses atomic members to ensure
    safe read and write operations.

        To allow all sub-operations to log only their own progress, this class
    will also log the number of subtasks to process in the entire main process.
*/

class ProgressLogger
{
public:
    ProgressLogger();
    ~ProgressLogger();

    int GetProgress();
    void SetProgress(int p);
    void SetTaskNumber(int n);
    void IncrementFinishedTasksCpt();
    void ResetFinishTasksCpt();

    bool IsProcessing();
    void SetIsProcessing(bool b);

private:
    // progress counters
    std::atomic<int> *progress;
    std::atomic<int> *task_number;
    std::atomic<int> *finished_tasks_cpt;

    // processing flag
    std::atomic<bool> *is_processing;
};

#endif // PROGRESSLOGGER_H
