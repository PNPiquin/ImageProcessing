#ifndef PROGRESSLOGGER_H
#define PROGRESSLOGGER_H

#include <atomic>

class ProgressLogger
{
public:
    ProgressLogger();

    int GetProgress();
    void SetProgress(int p);

private:
    std::atomic<int> *progress;
};

#endif // PROGRESSLOGGER_H
