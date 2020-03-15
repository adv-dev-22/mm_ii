#ifndef _THREADS_STOP_INDICATOR_H_
#define _THREADS_STOP_INDICATOR_H_

#include <QObject>

class ThreadsStopIndicator : public QObject {
Q_OBJECT
public:
    explicit ThreadsStopIndicator(QObject *parent = nullptr);

    /*! Set up the number of therads. */
    void set_number(size_t number);

signals:
    void all_threads_are_done();

public slots:
    void checkout(int index);

private:
    /*! Total number of threads waiting to be finished. */
    size_t total_number_;

    /*! How many are finished already. */
    size_t current_number_;
};

#endif // THREADS_STOP_INDICATOR_H
