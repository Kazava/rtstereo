#include "renderer.hpp"
#include <stdio.h>
//#include <cv.h>

SDispUnit g_dispUnit3d;

//using namespace std;

static float g_ratio;
static int g_Width = 600;                          // Initial window width
static int g_Height = 600;                         // Initial window height
static GLfloat g_nearPlaneForDefaultRender = -100;//0.01;
static GLfloat g_farPlaneForDefaultRender = 1000;

GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};  /* Red diffuse light. */
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */


//View Change by Mouse
static bool g_bButton1Down = false;
static float g_xClick = 0;
static float g_yClick = 0;

float g_fViewDistance = -82.3994; //-45;
float g_mouseXRotate = -63.2; //0;
float g_mouseYRotate = 7; //60;
float g_mouseXPan = -69.2; // 0;
float g_mouseYPan = -29.9501; // 0;
float g_mouseZPan = 0;
float g_scaleForMouseMotion =0.1;

enum cam_mode {CAM_DEFAULT=0,  CAM_ROTATE, CAM_ZOOM, CAM_PAN, CAM_PAN_Z};
static cam_mode g_camMode=CAM_DEFAULT;

//#define RADPERDEG 0.0174533
const auto RADPERDEG = 0.0174532925199433;


void DrawConeByTwoPts(cv::Point3f& pt1,cv::Point3f& pt2,float ptSize)
{
  GLdouble x1 =pt1.x;
  GLdouble y1 =pt1.y;
  GLdouble z1 =pt1.z;
  GLdouble x2 =pt2.x;
  GLdouble y2 =pt2.y;
  GLdouble z2 =pt2.z;

  double x=x2-x1;
  double y=y2-y1;
  double z=z2-z1;
  //double L=std::sqrt(x*x+y*y+z*z);

  glPushMatrix ();

  glTranslated(x1,y1,z1);

  if((x!=0.)||(y!=0.)) {
    glRotated(std::atan2(y,x)/RADPERDEG,0.,0.,1.);
    glRotated(std::atan2(std::sqrt(x*x+y*y),z)/RADPERDEG,0.,1.,0.);
  } else if (z<0){
    glRotated(180,1.,0.,0.);
  }

  //double height = Distance(pt1,pt2);
  double height = sqrt((pt1.x - pt2.x)*(pt1.x - pt2.x) +  (pt1.y - pt2.y)*(pt1.y - pt2.y)   + (pt1.z - pt2.z)*(pt1.z - pt2.z) );
  glutSolidCone(ptSize,height,5,5);
  //glutSolidCone(3,height,10,10);

  glPopMatrix();
}


void RenderHumanBody()
{

  /*for(int part=0;part<19;++part)
    {

      //const op::Array<float>& poseKeyPoints = (*g_dispUnit3d.m_poseKeyPoints);
      if(g_dispUnit3d.m_poseKeyPoints[3*part+2]>0)
      {
        //printf("%d: %f, %f, %f\n",part, g_dispUnit3d.m_poseKeyPoints[3*part]/1280, g_dispUnit3d.m_poseKeyPoints[3*part+1]/720, g_dispUnit3d.m_poseKeyPoints[3*part+2]);
        glPushMatrix();
          glTranslatef(-(g_dispUnit3d.m_poseKeyPoints[3*part] -640 )/1280*30 , -(g_dispUnit3d.m_poseKeyPoints[3*part+1]-360)/720*30,0);
          glutWireSphere(0.5,25,25);
        glPopMatrix();
      }
      //
    }*/

  //const auto numberPeople = g_dispUnit3d.m_poseKeyPoints.getSize(0);
  const auto numberBodyParts = g_dispUnit3d.m_poseKeyPoints.getSize(1);
  int person=0;
  //for(int person=0;person<numberPeople;++person)
  {
    for(unsigned int part=0;part<numberBodyParts;++part)
    {
      //glColor4f(skeleton.m_jointPos[i].second.color.x,skeleton.m_jointPos[i].second.color.y,skeleton.m_jointPos[i].second.color.z,skeleton.m_jointPos[i].second.alpha);
      //glColor4f(1,1,0,1);
      GLfloat colorDiffuse[] = {0.0,1.0,1.0,1.0};
      GLfloat colorAmbient[] = {0.0,0.7,0.7,1.0};
//      GLfloat colorSpecular[] = {1.0,1.0,1.0,1.0};
      glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,colorAmbient);
      glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,colorDiffuse);
//      glMaterialfv(GL_FRONT, GL_SPECULAR, colorSpecular);
//      if(g_dispOptions.m_showLightOn)
//      {
//        Point3f ambient = skeleton.m_jointPos[i].second.color;
//        ambient = ambient*0.7;
//        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,(GLfloat*)&ambient.x);
//        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,(GLfloat*)&skeleton.m_jointPos[i].second.color.x);
//      glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat*)&g_black_p3f.x);
        //    glMaterialf(GL_FRONT, GL_SHININESS, 20); - See more at: http://www.codemiles.com/c-opengl-examples/adding-lighting-to-a-solid-sphere-t9125.html#sthash.IYzNBlnU.dpuf
//      }

      /*if(skeleton.m_relatedPartTrajProp[i].first==2)      //means selected bone to be visulized with alpha
        glColor4f(skeleton.m_jointPos[i].second.x,skeleton.m_jointPos[i].second.y,skeleton.m_jointPos[i].second.z,0.2f);
      else*/
      if(g_dispUnit3d.m_poseKeyPoints[4*part+2 + person*numberBodyParts] > 0)
      {
        glPushMatrix();
        //glTranslatef(skeleton.m_jointPos[i].first.x,skeleton.m_jointPos[i].first.y,skeleton.m_jointPos[i].first.z);
        glTranslatef(-(g_dispUnit3d.m_poseKeyPoints[4*part + person*numberBodyParts] -640 )/1280*30,
                     -(g_dispUnit3d.m_poseKeyPoints[4*part+1+ person*numberBodyParts]-360)/720*30,
                     -(g_dispUnit3d.m_poseKeyPoints[4*part+2+ person*numberBodyParts]-360)/720*30
//                     0
        );

        if(part==4 || part==7)
          glutSolidSphere(0.5*0.7,20,20);
        else
          glutSolidSphere(0.5,20,20);
        //glutSolidSphere(20/WORLD_TO_CM_RATIO,20,20);
        glPopMatrix();
      }
    }

    int parentIdx[] ={1, -1, 1, 2, 3, 1, 5, 6, 1, 8, 9, 1, 11, 12, 0, 0, 14, 15};
    //Bone
    //0-1-2 1-3-4-5 0-6-7 6-8-9-10
    //int sizeOfJoints = skeleton.m_boneEndsPos.size();
    //sizeOfJoints /=2;
    for(int part=0;part<numberBodyParts;++part)
    {
      /*if(skeleton.m_label==SKELETON_3DPS_Compare && g_dispOptions.m_trajDrawColorMode!=2)
        glColor3f(0,1,1);
      else*/
      //glColor4f(skeleton.m_boneEndsPos[2*i].second.color.x,skeleton.m_boneEndsPos[2*i].second.color.y,skeleton.m_boneEndsPos[2*i].second.color.z,skeleton.m_boneEndsPos[2*i].second.alpha);
        //glColor4f(skeleton.m_boneEndsPos[2*i].second.color.x,skeleton.m_boneEndsPos[2*i].second.color.y,skeleton.m_boneEndsPos[2*i].second.color.z,0.4);

      /*if(g_dispOptions.m_showLightOn)
      {
        Point3f ambient = skeleton.m_boneEndsPos[2*i].second.color;

        ambient = ambient*0.7;
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT,(GLfloat*)&ambient.x);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE,(GLfloat*)&skeleton.m_boneEndsPos[2*i].second.color.x);
        //glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat*)&g_black_p3f.x);
        //    glMaterialf(GL_FRONT, GL_SHININESS, 20); - See more at: http://www.codemiles.com/c-opengl-examples/adding-lighting-to-a-solid-sphere-t9125.html#sthash.IYzNBlnU.dpuf
      }*/
      if(parentIdx[part]>=0)
      {
        if(g_dispUnit3d.m_poseKeyPoints[4*part+3 + person*numberBodyParts]>0)
        {
          cv::Point3f child(
            -(g_dispUnit3d.m_poseKeyPoints[4*part + person*numberBodyParts] - 640 ) / 1280*30,
            -(g_dispUnit3d.m_poseKeyPoints[4*part+1 + person*numberBodyParts] - 360) / 720*30,
            -(g_dispUnit3d.m_poseKeyPoints[4*part+2 + person*numberBodyParts] - 360) / 720*30
//            0
          );
          cv::Point3f parent(
            -(g_dispUnit3d.m_poseKeyPoints[4*parentIdx[part]+ person*numberBodyParts] -640 )/1280*30 ,
            -(g_dispUnit3d.m_poseKeyPoints[4*parentIdx[part]+1+ person*numberBodyParts]-360)/720*30,
            -(g_dispUnit3d.m_poseKeyPoints[4*parentIdx[part]+2+ person*numberBodyParts]-360)/720*30
//            0
          );
          DrawConeByTwoPts(parent,child,0.5);
        }
      }
    }
  }
}


void InitGraphics(void)
{
      /* Enable a single OpenGL light. */
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_diffuse);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);

  /* Use depth buffering for hidden surface elimination. */
  glEnable(GL_DEPTH_TEST);

  /* Setup the view of the cube. */
  glMatrixMode(GL_PROJECTION);
  gluPerspective( /* field of view in degree */ 40.0,
    /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 1000.0);
  glMatrixMode(GL_MODELVIEW);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */

  /* Adjust cube position to be asthetic angle. */
  glTranslatef(0.0, 0.0, -1.0);
  glRotatef(60, 1.0, 0.0, 0.0);
  glRotatef(-20, 0.0, 0.0, 1.0);

  glColorMaterial(GL_FRONT, GL_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}


// this is the actual idle function
void IdleFunc()
{
    glutPostRedisplay();
  glutSwapBuffers();
}


void reshape(GLint width, GLint height)
{
   g_Width = width;
   g_Height = height;
   //printf("Window Reshape: %d, %d\n",width,height);
   glViewport(0, 0, g_Width, g_Height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   g_ratio = (float)g_Width / g_Height;
   gluPerspective(65.0, g_ratio, g_nearPlaneForDefaultRender, g_farPlaneForDefaultRender);
   glMatrixMode(GL_MODELVIEW);
}

using namespace cv;
void RenderDomeFloor()
{
  glDisable(GL_LIGHTING);
  //Point3f g_floorCenter = Point3f(182.951, 492.528, 1913.75);   //ankle
  //Point3f Noise(190.819, - 958.718, 1626.54);

  Point3f g_floorCenter = Point3f(0,0,0);   //ankle
  Point3f Noise(0,1,0);

  Point3f upright = Noise - g_floorCenter;
  upright = 1.0/sqrt(upright.x *upright.x +  upright.y *upright.y + upright.z *upright.z )*upright;
  Point3f g_floorAxis1(1,0,0);
  Point3f g_floorAxis2 = g_floorAxis1.cross(upright);
  g_floorAxis1 = g_floorAxis2.cross(upright);

  int gridNum = 10;
  double width = 50;//sqrt(Distance(g_floorPts.front(),g_floorCenter)*2 /gridNum) * 1.2;
  //double halfWidth =width/2;
  Point3f origin =  g_floorCenter - g_floorAxis1*(width*gridNum/2 ) - g_floorAxis2*(width*gridNum/2);
  Point3f axis1 =  g_floorAxis1 * width;
  Point3f axis2 =  g_floorAxis2 * width;
  for(int y=0;y<=gridNum;++y)
    for(int x=0;x<=gridNum;++x)
    {
      if((x+y)%2 ==0)
        //continue;
        //if(g_visData.m_backgroundColor.x ==0)
          glColor4f(0.2,0.2,0.2,1.0f); //black
        //else
        //  glColor4f(1.0f,1.0f,1.0f,1.0f); //white
      else
        //glColor4f(0.02,0.02,0.02,1);; //grey
      {
        //if(g_visData.m_backgroundColor.x ==0) //black background
          glColor4f(0.5,0.5,0.5,1); //grey
        //else
        //  glColor4f(0.9,0.9,0.9,1); //grey
      }

      Point3f p1 = origin + axis1*x + axis2*y;
      Point3f p2 = p1+ axis1;
      Point3f p3 = p1+ axis2;
      Point3f p4 = p1+ axis1 + axis2;


      glBegin(GL_QUADS);

    //    glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(   p1.x, p1.y,p1.z);
        //glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(   p2.x, p2.y,p2.z);
      //  glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(   p4.x, p4.y,p4.z);
      //  glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(   p3.x, p3.y,p3.z);
      glEnd();
    }
  glEnable(GL_LIGHTING);
}

void RenderMain(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  //gluLookAt(0,0,0, 0, 0, 1, 0, -1, 0);
  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
  0.0, 0.0, 0.0,      /* center is at (0,0,0) */
  0.0, 1.0, 0.);      /* up is in positive Y direction */


  glTranslatef(0,0,g_fViewDistance);
  glRotatef(-g_mouseYRotate,1,0,0);
  glRotatef(-g_mouseXRotate,0,1,0);
  //glRotatef(g_rotateAngle,0,0,1);

  glTranslatef(-g_mouseXPan,g_mouseYPan,-g_mouseZPan);
//  -82.3994 6.99997 -63.2			-69.2 -29.9501 0
//std::cout << g_fViewDistance << " "  << g_mouseYRotate<< " "  << g_mouseXRotate << "\t\t\t";
//std::cout << g_mouseXPan << " "  << g_mouseYPan<< " "  << g_mouseZPan << std::endl;
  //glTranslatef(g_dispUnit3d.m_pt.x,g_dispUnit3d.m_pt.y,-g_mouseZPan);
  //printf("    render: %f,%f\n",g_dispUnit3d.m_pt.x,g_dispUnit3d.m_pt.y);

  //////////////////////////////////////////////////////////////////////////
  // Transform to anchor a selected bone as origin
  //glTranslatef(-g_visData.m_anchorOrigin.x,-g_visData.m_
  //glColor3f(1,1,0);
  //glutWireTeapot(1);

  RenderDomeFloor();
  if(g_dispUnit3d.m_bValid)
  {
    RenderHumanBody();
    /*for(int part=0;part<19;++part)
    {

      //const op::Array<float>& poseKeyPoints = (*g_dispUnit3d.m_poseKeyPoints);
      if(g_dispUnit3d.m_poseKeyPoints[3*part+2]>0)
      {
        //printf("%d: %f, %f, %f\n",part, g_dispUnit3d.m_poseKeyPoints[3*part]/1280, g_dispUnit3d.m_poseKeyPoints[3*part+1]/720, g_dispUnit3d.m_poseKeyPoints[3*part+2]);
        glPushMatrix();
          glTranslatef(-(g_dispUnit3d.m_poseKeyPoints[3*part] -640 )/1280*30 , -(g_dispUnit3d.m_poseKeyPoints[3*part+1]-360)/720*30,0);
          glutWireSphere(0.5,25,25);
        glPopMatrix();
      }
      //
    }*/

  }

  glutSwapBuffers();
}

void MouseButton(int button, int state, int x, int y)
{

  if (button==3 || button==4) //mouse wheel
  {
    //printf("wheel:: %d, %d, %d, %d\n",button, state,x,y);
    if(button==3)  //zoom in
      g_fViewDistance += 10*g_scaleForMouseMotion;
    else  //zoom out
      g_fViewDistance -= 10*g_scaleForMouseMotion;
    //if(g_fViewDistance<0.01)
      //g_fViewDistance = 0.01;
    printf("g_fViewDistance: %f\n",g_fViewDistance);
  }
  else
  {
    if (button == GLUT_LEFT_BUTTON)
    {
      g_bButton1Down = (state == GLUT_DOWN) ? 1 : 0;
      g_xClick = x;
      g_yClick = y;


      //if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
        ///g_camMode = CAM_ROTATE;
      //else
      if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
        g_camMode = CAM_PAN;
      else
      {
        g_camMode = CAM_ROTATE;
      }
    }
    //printf("Clicked: %f,%f\n",g_xClick,g_yClick);
  }
  glutPostRedisplay();
}

void MouseMotion(int x, int y)
{

  // If button1 pressed, zoom in/out if mouse is moved up/down.
  if (g_bButton1Down)
  {
  /*  if(g_camMode == CAM_ZOOM)
    {
      g_fViewDistance += (y - g_yClick) * g_scaleForMouseMotion;

      printf("g_fViewDistance: %f\n",g_fViewDistance);
      //if (g_cameraWorks.m_currentViewStatus.fViewDistance < VIEWING_DISTANCE_MIN)
       // g_cameraWorks.m_currentViewStatus.fViewDistance = VIEWING_DISTANCE_MIN;
    }
    else */
    if(g_camMode == CAM_ROTATE)
    {
      g_mouseXRotate += (x-g_xClick)*0.2;
      g_mouseYRotate -= (y-g_yClick)*0.2;
    }
    else if(g_camMode == CAM_PAN)
    {
      g_mouseXPan -= (x-g_xClick)/2*g_scaleForMouseMotion;
      g_mouseYPan -= (y-g_yClick)/2*g_scaleForMouseMotion;
    }
    else if(g_camMode == CAM_PAN_Z)
    {
      double dist = sqrt( pow((x-g_xClick),2.0f)+pow((y-g_yClick),2.0f));
      if(y<g_yClick)
        dist = -dist;
      g_mouseZPan -= dist/5*g_scaleForMouseMotion;
    }

    g_xClick = x;
    g_yClick = y;

    //printf("%f,%f\n",g_xClick,g_yClick);
    glutPostRedisplay();
  }
}
