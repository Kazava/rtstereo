#ifndef OPENPOSE__GUI__W_ADD_GUI_INFO_HPP
#define OPENPOSE__GUI__W_ADD_GUI_INFO_HPP

#include "guiInfoAdder.hpp"
#include "../thread/worker.hpp"

namespace op
{
    template<typename TDatums>
    class WGuiInfoAdder : public Worker<TDatums>
    {
    public:
        explicit WGuiInfoAdder(const std::shared_ptr<GuiInfoAdder>& guiInfoAdder);

        void initializationOnThread();

        void work(TDatums& tDatums);

    private:
        std::shared_ptr<GuiInfoAdder> spGuiInfoAdder;

        DELETE_COPY(WGuiInfoAdder);
    };
}





// Implementation
#include "../utilities/errorAndLog.hpp"
#include "../utilities/macros.hpp"
#include "../utilities/pointerContainer.hpp"
#include "../utilities/profiler.hpp"
namespace op
{
    template<typename TDatums>
    WGuiInfoAdder<TDatums>::WGuiInfoAdder(const std::shared_ptr<GuiInfoAdder>& guiInfoAdder) :
        spGuiInfoAdder{guiInfoAdder}
    {
    }

    template<typename TDatums>
    void WGuiInfoAdder<TDatums>::initializationOnThread()
    {
    }

    template<typename TDatums>
    void WGuiInfoAdder<TDatums>::work(TDatums& tDatums)
    {
        try
        {
            if (checkNoNullNorEmpty(tDatums))
            {
                // Debugging log
                dLog("", Priority::Low, __LINE__, __FUNCTION__, __FILE__);
                // Profiling speed
                const auto profilerKey = Profiler::timerInit(__LINE__, __FUNCTION__, __FILE__);
                // Add GUI components to frame
                std::vector<cv::Mat> cvOutputDatas{tDatums->size()};
                std::vector<Array<float>> poseKeyPointsVector{tDatums->size()};
                for (auto i = 0 ; i < tDatums->size() ; i++)
                {
                    cvOutputDatas[i] = (*tDatums)[i].cvOutputData;
                    poseKeyPointsVector[i] = (*tDatums)[i].poseKeyPoints;
                }
                spGuiInfoAdder->addInfo(cvOutputDatas, poseKeyPointsVector, (*tDatums)[0].id, (*tDatums)[0].elementRendered.second);
                // Profiling speed
                Profiler::timerEnd(profilerKey);
                Profiler::printAveragedTimeMsOnIterationX(profilerKey, __LINE__, __FUNCTION__, __FILE__, Profiler::DEFAULT_X);
                // Debugging log
                dLog("", Priority::Low, __LINE__, __FUNCTION__, __FILE__);
            }
        }
        catch (const std::exception& e)
        {
            this->stop();
            tDatums = nullptr;
            error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        }
    }

    COMPILE_TEMPLATE_DATUM(WGuiInfoAdder);
}

#endif // OPENPOSE__GUI__W_ADD_GUI_INFO_HPP
