#pragma once

#include <GL/glut.h>
#include <vector>
//using namespace std;
#include <openpose/headers.hpp>
#include "datum3D.hpp"

struct SDispUnit
{
    //std::shared_ptr<op::Array<float>> m_poseKeyPoints;
    op::Array<float> m_poseKeyPoints;
    //cv::Point3f m_pt;
    bool m_bValid;
};

//void display(void);
void RenderMain();
void InitGraphics(void);
void IdleFunc();
void reshape(GLint width, GLint height);

void SpecialInput(int key, int x, int y);
void Keyboard(unsigned char key, int x, int y);
void MouseButton(int button, int state, int x, int y);
void MouseMotion(int x, int y);

extern SDispUnit g_dispUnit3d;





// This worker will do 3-D rendering
const auto GUI_NAME = "OpenPose 3-D";
class WRender3D : public op::WorkerConsumer<std::shared_ptr<std::vector<Datum3D>>>
{
public:
    inline static void* VisualizationThread(void*)
    {
        char *my_argv[] = { "myprogram", NULL };
        int   my_argc = 1;
        glutInit(&my_argc, my_argv);

        /* setup the size, position, and display mode for new windows */
        glutInitWindowSize(1280,720);
//        glutInitWindowSize(640,480);
        glutInitWindowPosition(200,0);
        //  glutSetOption(GLUT_MULTISAMPLE,8);
        glutInitDisplayMode ( GLUT_RGBA  | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

        /* create and set up a window */
        glutCreateWindow(GUI_NAME);
        InitGraphics();
        glutDisplayFunc(RenderMain);
        glutMouseFunc(MouseButton);
        glutMotionFunc(MouseMotion);
        glutIdleFunc (IdleFunc);
        /*glutKeyboardFunc (Keyboard);
        glutSpecialFunc(SpecialInput);

        */
        //glutReshapeFunc (reshape);
        //

        glutMainLoop();
        return NULL;
    }

    WRender3D()
    {
        cv::imshow(GUI_NAME, cv::Mat{500, 500, CV_8UC3, cv::Scalar{0,0,0}});

        //Run OpenGL
        int err;
        err = pthread_create(&render3d_tid,NULL, &WRender3D::VisualizationThread, NULL);
        if(err !=0)
            printf("\ncan't creat render3D thread\n");
    }

    void initializationOnThread() {}

    void workConsumer(const std::shared_ptr<std::vector<Datum3D>>& datumsPtr)
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

                // OpenGL Rendering
                g_dispUnit3d.m_poseKeyPoints = datumsPtr->at(0).poseKeyPoints3D;
                g_dispUnit3d.m_bValid = true;

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
private:
    pthread_t render3d_tid;
};
