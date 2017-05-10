#pragma once

#include <openpose/headers.hpp>
#include "datum3D.hpp"

// This worker will do 3-D rendering
const auto GUI_NAME = "OpenPose 3-D";
class WRender3D : public op::WorkerConsumer<std::shared_ptr<std::vector<Datum3D>>>
{
public:
    WRender3D();

    void initializationOnThread() {}

    void workConsumer(const std::shared_ptr<std::vector<Datum3D>>& datumsPtr);
private:
    pthread_t mRender3dTid;
};
