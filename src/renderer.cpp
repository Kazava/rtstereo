#include "renderer.hpp"

WRender3D::WRender3D()
{
    cv::imshow(GUI_NAME, cv::Mat{500, 500, CV_8UC3, cv::Scalar{0,0,0}});
}

void WRender3D::workConsumer(const std::shared_ptr<std::vector<Datum3D> > &datumsPtr)
{
    try
    {
        // Profiling speed
        const auto profilerKey = op::Profiler::timerInit(__LINE__, __FUNCTION__, __FILE__);

        // User's displaying/saving/other processing here
        // datum.cvOutputData: rendered frame with pose or heatmaps
        // datum.poseKeyPoints: Array<float> with the estimated pose
        if (datumsPtr != nullptr && !datumsPtr->empty())
        {
            cv::Mat cvMat = datumsPtr->at(0).cvOutputData.clone();
            for (auto i = 1u ; i < datumsPtr->size() ; i++)
                cv::hconcat(cvMat, datumsPtr->at(i).cvOutputData, cvMat);

            // while (cvMat.cols > 1500 || cvMat.rows > 1500)
            while (cvMat.cols > 1920 || cvMat.rows > 1920)
                // while (cvMat.rows > 3500)
                cv::pyrDown(cvMat, cvMat);

            cv::imshow(GUI_NAME, cvMat);
            cv::resizeWindow(GUI_NAME, cvMat.cols, cvMat.rows);

            // Profiling speed
            op::Profiler::timerEnd(profilerKey);
            op::Profiler::printAveragedTimeMsOnIterationX(profilerKey, __LINE__, __FUNCTION__, __FILE__, 100);
        }

        const auto key = cv::waitKey(1) % 256; // It sleeps 1 ms just to let the user see the output. Change to 33ms for normal 30 fps display
        if (key == 27 || key == 'q')
            this->stop();
    }
    catch (const std::exception& e)
    {
        op::log("Some kind of unexpected error happened.");
        this->stop();
        op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
    }
}
