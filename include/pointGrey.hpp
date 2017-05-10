#ifndef POINT_GREY_HPP
#define POINT_GREY_HPP

#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <opencv2/opencv.hpp>
#include <Spinnaker.h>
#include <SpinGenApi/SpinnakerGenApi.h>
#include <openpose/headers.hpp>
#include "datum3D.hpp"

// Camera 1
const cv::Mat intrinsics1 = (cv::Mat_<double>(3,3) << 817.93481631740565, 0, 600.70689997785121,
                                                      0, 816.51774059837908, 517.84529566329593,
                                                      0, 0, 1);
const cv::Mat distortion1 = (cv::Mat_<double>(8,1) <<
    -1.8102158829399091, 9.1966147162623262, -0.00044293900343777355, 0.0013638377686816653, 1.3303863414979364, -1.418905163635487, 8.4725535468475819, 4.7911023525901033);
const cv::Mat intrinsics2 = (cv::Mat_<double>(3,3) << 816.20921132436638, 0, 612.67087968681585,
                                                      0, 816.18292222910486, 530.47901782670431,
                                                      0, 0, 1);
// Camera 2
const cv::Mat distortion2 = (cv::Mat_<double>(8,1) <<
    -5.1088507540294881, 133.63995617304997, -0.0010048069080912836, 0.00018825291386406282, 20.688286893903879, -4.7604289550474768, 132.42412342224557, 70.01195364029752);
const cv::Mat intrinsics3 = (cv::Mat_<double>(3,3) << 798.42980806905666, 0, 646.48130011561727,
                                                      0, 798.46535448393979, 523.91590563194586,
                                                      0, 0, 1);
// Camera 3
const cv::Mat distortion3 = (cv::Mat_<double>(8,1) <<
    -0.57530495294002304, -0.54721992620722582, -0.00037614702677289967, -0.00081995658363481598, -0.020321660897680775, -0.18040544059116842, -0.87724444571603022, -0.13136636671099691);
// Rotation/pose between cameras
const cv::Mat M_2_1 = (cv::Mat_<double>(3,4) << 0.99996250486269234, 0.0017615516377958358, -0.0084785496729892478, 238.41898703108865,
                                                -0.0016586205150361947, 0.99992502970465924, 0.01213193917407162, -5.3466981906472313,
                                                0.0084992850709379297, -0.012117421588921106, 0.99989045912405794, -13.837195278925094);
                                                //0, 0, 0, 1);
const cv::Mat M_3_1 = (cv::Mat_<double>(3,4) << 0.99580944212407108, 0.0016504645521041869, -0.091437579491741208, 465.16336192832034,
                                                -0.00047310479689230813, 0.99991672756284955, 0.012896282869621009, -7.2630059217714233,
                                                0.091451250119380004, -0.012798980692397748, 0.99572729948758476, -20.953563927586401);
                                                //0, 0, 0, 1);
// M_3_1 MUST BE WRONG!!!!!!!!!!!!!!! X distance too small!!!!!!!!!!!!!!!!!!
const cv::Mat M_3_2 = (cv::Mat_<double>(3,4) << 0.99964411542362097, 0.0020164611073378025, 0.026600307959287642, 235.24611858668919,
                                                -0.0019450108867412963, 0.99999443188035586, -0.0027116675560930285, -9.9913557169930129,
                                                -0.026605627817753243, 0.002658964626862062, 0.99964247132439121, -2.0500957730239975);
                                                //0, 0, 0, 1);
// Manually inverted
const cv::Mat M_1_2 = (cv::Mat_<double>(3,4) << 0.999962504862692,  -0.00165862051503619,   0.00849928507093793,    -238.301309354482,
                                                0.00176155163779584,    0.999925029704659,  -0.0121174215889211,    4.75863886121558,
                                                -0.00847854967298925,   0.0121319391740716, 0.999890459124058,  15.9219925821916);
const cv::Mat M_1_3 = (cv::Mat_<double>(3,4) << 0.995809442124071,  -0.000473104796892308,  0.0914512501193800, -461.301274485705,
                                                0.00165046455210419,    0.999916727562850,  -0.0127989806923977,    6.22648121362088,
                                                -0.0914375794917412,    0.0128962828696210, 0.995727299487585,  63.4911132860733);
const cv::Mat M_2_3 = (cv::Mat_<double>(3,4) << 0.999644115423621,  -0.00194501088674130,   -0.0266056278177532,    -235.236375502202,
                                                0.00201646110733780,    0.999994431880356,  0.00265896462686206,    9.52238656728889,
                                                0.0266003079592876, -0.00271166755609303,   0.999642471324391,  -4.23534963077479);
const std::vector<cv::Mat> intrinsics{intrinsics1, intrinsics2, intrinsics3};
const std::vector<cv::Mat> distortions{distortion1, distortion2, distortion3};
// const std::vector<cv::Mat> MOnEachCamera{intrinsics1 * cv::Mat::eye(3,4, CV_64F), intrinsics2 * M_2_1, intrinsics3 * M_3_1};
const std::vector<cv::Mat> MOnEachCamera{intrinsics1 * cv::Mat::eye(3,4, CV_64F), intrinsics2 * M_1_2, intrinsics3 * M_1_3};

// The W-classes can be implemented either as a template or as simple classes given
// that the user usually knows which kind of data he will move between the queues,
// in this case we assume a std::shared_ptr of a std::vector of Datum3D

// This worker will just read and return all the jpg files in a directory
class WPointGrey : public op::WorkerProducer<std::shared_ptr<std::vector<Datum3D>>>
{
public:
    WPointGrey();

    ~WPointGrey();

    void initializationOnThread();

    std::shared_ptr<std::vector<Datum3D>> workProducer();

private:
    bool initialized;
    Spinnaker::CameraList mCameraList;
    Spinnaker::SystemPtr mSystemPtr;
};

#endif // POINT_GREY_HPP
