#ifndef _COMPUTE_THREAD_H_
#define _COMPUTE_THREAD_H_

#include <QThread>

template <typename T> class BaseDensityEngine;

class ComputeDensityThread : public QThread {
Q_OBJECT
public:
    ComputeDensityThread();
    virtual ~ComputeDensityThread();

    void set_engine(BaseDensityEngine<double> * density_eng);

protected:
    virtual void run();

private:
    BaseDensityEngine<double> * density_engine_;
};

#endif  // _COMPUTE_THREAD_H_

// End of the file

