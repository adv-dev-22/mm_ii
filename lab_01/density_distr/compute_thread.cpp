#include "compute_thread.h"
#include "density_engine.h"

ComputeDensityThread::ComputeDensityThread():
QThread(),
density_engine_(nullptr) {

}

//virtual
ComputeDensityThread::~ComputeDensityThread() {
    density_engine_ = nullptr;
}

void ComputeDensityThread::set_engine(BaseDensityEngine<double> * density_eng) {
    density_engine_ = density_eng;
}

//virtual
void ComputeDensityThread::run() {

    if (nullptr == density_engine_) throw std::invalid_argument("nullptr engine at thread run.");

    density_engine_->compute();
}

// End of the file

