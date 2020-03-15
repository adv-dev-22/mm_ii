#include "threads_stop_indicator.h"

ThreadsStopIndicator::ThreadsStopIndicator(QObject *parent):
QObject(parent),
total_number_(0),
current_number_(0) {

}

void ThreadsStopIndicator::set_number(size_t number) {
    total_number_ = number;
}

void ThreadsStopIndicator::checkout(int index) {


    // mutex
}

// End of the file
