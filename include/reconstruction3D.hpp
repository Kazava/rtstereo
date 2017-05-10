#ifndef RECONSTRUCTION_3D_HPP
#define RECONSTRUCTION_3D_HPP

#include "datum3D.hpp"

// This worker will do 3-D reconstruction
class WReconstruction3D : public op::Worker<std::shared_ptr<std::vector<Datum3D>>>
{
public:
    void initializationOnThread() {}

    void work(std::shared_ptr<std::vector<Datum3D>>& datumsPtr);
};

#endif // RECONSTRUCTION_3D_HPP
