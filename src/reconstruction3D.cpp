#include <opencv2/opencv.hpp>
#include "pointGrey.hpp"
#include "reconstruction3D.hpp"

double calcReprojectionError(const cv::Mat& X, const std::vector<cv::Mat>& M, const std::vector<cv::Point2d>& pt2D)
{
    double averageError = 0;
    for(unsigned int i = 0 ; i < M.size() ; i++)
    {
        //printMatrix("M",*M[i]);
        //printMatrix("X",X);
        cv::Mat imageX = M[i] * X;
        imageX /= imageX.at<double>(2,0);
        double error = std::sqrt(std::pow(imageX.at<double>(0,0) -  pt2D[i].x,2) + std::pow(imageX.at<double>(1,0) - pt2D[i].y,2));
        //printfLog("error %f",error);
        averageError += error;
    }
    return averageError / M.size();
}

void triangulate(cv::Mat& X, const std::vector<cv::Mat>& MOnEachCamera, const std::vector<cv::Point2d>& pointOnEachCamera)
{
    // Security checks
    if (MOnEachCamera.empty() || MOnEachCamera.size() != pointOnEachCamera.size())
        op::error("numberCameras.empty() || numberCameras.size() != pointOnEachCamera.size()", __LINE__, __FUNCTION__, __FILE__);
    // Create and fill A
    const auto numberCameras = (int)MOnEachCamera.size();
    cv::Mat A = cv::Mat::zeros(numberCameras*2, 4, CV_64F);
    for (auto i = 0 ; i < numberCameras ; i++)
    {
        cv::Mat temp = pointOnEachCamera[i].x*MOnEachCamera[i].rowRange(2,3) - MOnEachCamera[i].rowRange(0,1);
        temp.copyTo(A.rowRange(i*2,i*2+1));
        temp = pointOnEachCamera[i].y*MOnEachCamera[i].rowRange(2,3) - MOnEachCamera[i].rowRange(1,2);
        temp.copyTo(A.rowRange(i*2+1,i*2+2));
    }
    // SVD on A
    cv::SVD svd{A};
    svd.solveZ(A,X);
    X /= X.at<double>(3);
}

// TODO: ask Hanbyul for the missing function: TriangulationOptimization
double triangulateWithOptimization(cv::Mat& X, const std::vector<cv::Mat>& MOnEachCamera, const std::vector<cv::Point2d>& pointOnEachCamera)
{
    triangulate(X, MOnEachCamera, pointOnEachCamera);

    // //if (MOnEachCamera.size() >= 3)
    // //double beforeError = calcReprojectionError(&MOnEachCamera, pointOnEachCamera, X);
    // double change = TriangulationOptimization(&MOnEachCamera, pointOnEachCamera, X);
    // //double afterError = calcReprojectionError(&MOnEachCamera,pointOnEachCamera,X);
    // //printfLog("!!Mine %.8f , inFunc %.8f \n",beforeError-afterError,change);
    // return change;
    return 0.;
}

void WReconstruction3D::work(std::shared_ptr<std::vector<Datum3D>>& datumsPtr)
{
    // User's post-processing (after OpenPose processing & before OpenPose outputs) here
        // datum.cvOutputData: rendered frame with pose or heatmaps
        // datum.poseKeyPoints: Array<float> with the estimated pose
    try
    {
        // Profiling speed
        const auto profilerKey = op::Profiler::timerInit(__LINE__, __FUNCTION__, __FILE__);
        if (datumsPtr != nullptr && /*!datumsPtr->empty() &&*/ datumsPtr->size() == 3)
        {
            auto& userDatum = datumsPtr->at(0);
//                const auto imageSize = datumsPtr->at(0).cvOutputData.size();
            // userDatum.poseKeyPoints = datumsPtr->at(0).poseKeyPoints.clone();
            const auto& pose0 = datumsPtr->at(0).poseKeyPoints;
            const auto& pose1 = datumsPtr->at(1).poseKeyPoints;
            const auto& pose2 = datumsPtr->at(2).poseKeyPoints;
            // const auto& datum2 = datumsPtr->at(0).poseKeyPoints.getSize(2);
            if (pose0.getSize(0) > 0 && pose1.getSize(0) > 0 && pose2.getSize(0) > 0)
            {
                // Count #correspondences
                const auto threshold = 0.1f;
                const auto numberBodyParts = pose0.getSize(1);
                std::vector<int> indexesUsed;
                std::vector<std::vector<cv::Point2d>> xyPoints;
                for (auto part = 0 ; part < numberBodyParts ; part++)
                {
                    if (pose0[{0, part, 2}] > threshold && pose1[{0, part, 2}] > threshold && pose2[{0, part, 2}] > threshold)
                    {
                        indexesUsed.emplace_back(part);
                        xyPoints.emplace_back(std::vector<cv::Point2d>{
                            cv::Point2d{pose0[{0, part, 0}], pose0[{0, part, 1}]},
                            cv::Point2d{pose1[{0, part, 0}], pose1[{0, part, 1}]},
                            cv::Point2d{pose2[{0, part, 0}], pose2[{0, part, 1}]}
                        });
                    }
                }
                if (!xyPoints.empty())
                {
                    // Do 3D reconstruction
                    std::vector<cv::Point3d> xyzPoints(xyPoints.size());
                    for (auto i = 0u ; i < xyPoints.size() ; i++)
                    {
                        cv::Mat X;
                        triangulateWithOptimization(X, MOnEachCamera, xyPoints[i]);
                        xyzPoints[i] = cv::Point3d{X.at<double>(0), X.at<double>(1), X.at<double>(2)};
                    }

                    // 3D points to pose
                    // OpenCV alternative:
                    // // http://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html#triangulatepoints
                    // cv::Mat reconstructedcv::Points{4, firstcv::Points.size(), CV_64F};
                    // cv::triangulatecv::Points(cv::Mat::eye(3,4, CV_64F), M_3_1, firstcv::Points, secondcv::Points, reconstructedcv::Points);
                    // // cv::triangulatecv::Points(cv::Mat::eye(3,4, CV_64F), M_1_3, firstcv::Points, secondcv::Points, reconstructedcv::Points);
                    userDatum.poseKeyPoints3D = op::Array<float>{{1, numberBodyParts, 4}, 0};
                    // auto maxX = 0.f;
                    // auto minX = 0.f;
                    // auto maxY = 0.f;
                    // auto minY = 0.f;
                    // auto maxZ = 0.f;
                    // auto minZ = 0.f;
                    for (auto index = 0u ; index < indexesUsed.size() ; index++)
                    {
                        auto& xValue = userDatum.poseKeyPoints3D[{0, indexesUsed[index], 0}];
                        auto& yValue = userDatum.poseKeyPoints3D[{0, indexesUsed[index], 1}];
                        auto& zValue = userDatum.poseKeyPoints3D[{0, indexesUsed[index], 2}];
                        auto& scoreValue = userDatum.poseKeyPoints3D[{0, indexesUsed[index], 3}];
                        if (std::isfinite(xyzPoints[index].x) && std::isfinite(xyzPoints[index].y) && std::isfinite(xyzPoints[index].z))
                        {
                            xValue = xyzPoints[index].x;
                            yValue = xyzPoints[index].y;
                            zValue = xyzPoints[index].z;
                            scoreValue = 1.f;
                        }
//                            if (indexesUsed[index] == 0) // Nose
//                                std::cout << xValue << " x " << yValue << " x " << zValue << std::endl;
//                            if (indexesUsed[index] == 10) // Right ankle
//                                std::cout << xValue << " x " << yValue << " x " << zValue << std::endl << std::endl;
                    }
                }
            }
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
