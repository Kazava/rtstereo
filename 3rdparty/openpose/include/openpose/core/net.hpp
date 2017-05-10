#ifndef OPENPOSE__CORE__NET_HPP
#define OPENPOSE__CORE__NET_HPP

namespace op
{
    class Net
    {
    public:
        virtual void initializationOnThread() = 0;

        // Alternative a) getInputDataCpuPtr or getInputDataGpuPtr + forwardPass()
        virtual float* getInputDataCpuPtr() const = 0;

        virtual float* getInputDataGpuPtr() const = 0;

        // Alternative b)
        virtual void forwardPass(const float* const inputData = nullptr) const = 0;
    };
}

#endif // OPENPOSE__CORE__NET_HPP
