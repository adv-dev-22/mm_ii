#include "threads_stop_indicator.h"
#include <QMutex>
#include <QDebug>

ThreadsStopIndicator::ThreadsStopIndicator(QObject *parent):
QObject(parent),
total_number_(0),
current_number_(0) {

}

void ThreadsStopIndicator::set_number(size_t number) {
    total_number_ = number;
}

void ThreadsStopIndicator::drop_counter() noexcept {
    current_number_ = 0;
}

void ThreadsStopIndicator::checkout() {

    qDebug() << " checkout worked ";

    QMutex mutex;
    mutex.lock();

    ++current_number_;

    if (total_number_ == current_number_) {
        qDebug() << "emit signal threads are done with id = " << current_number_;
        emit all_threads_are_done();
    }

    mutex.unlock();
}

// End of the file
