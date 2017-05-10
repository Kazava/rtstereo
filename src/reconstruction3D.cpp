#include <opencv2/opencv.hpp>
#include "pointGrey.hpp"
#include "reconstruction3D.hpp"

void WReconstruction3D::work(std::shared_ptr<std::vector<Datum3D>>& datumsPtr)
{
    // User's post-processing (after OpenPose processing & before OpenPose outputs) here
        // datum.cvOutputData: rendered frame with pose or heatmaps
        // datum.poseKeyPoints: Array<float> with the estimated pose
    try
    {
        // Profiling speed
        const auto profilerKey = op::Profiler::timerInit(__LINE__, __FUNCTION__, __FILE__);

        // 3-D reconstruction
        if (datumsPtr != nullptr && /*!datumsPtr->empty() &&*/ datumsPtr->size() == 3)
        {
            // auto& poseKeyPointsFromCamera0 = datumsPtr->at(0).poseKeyPoints;

            // Perform 3-D reconstruction here...

            // You might save the final 3-D reconstruction here:
            // datumsPtr->at(0).poseKeyPoints3D
        }

        // Profiling speed
        if (datumsPtr != nullptr && /*!datumsPtr->empty() &&*/ datumsPtr->size() == 4)
        {
            op::Profiler::timerEnd(profilerKey);
            op::Profiler::printAveragedTimeMsOnIterationX(profilerKey, __LINE__, __FUNCTION__, __FILE__, 100);
        }
    }
    catch (const std::exception& e)
    {
        op::log("Some kind of unexpected error happened.");
        this->stop();
        op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
    }
}
