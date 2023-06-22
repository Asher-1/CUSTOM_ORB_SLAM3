/**
* This file is part of ORB-SLAM3
*
* Copyright (C) 2017-2021 Carlos Campos, Richard Elvira, Juan J. Gómez Rodríguez, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
* Copyright (C) 2014-2016 Raúl Mur-Artal, José M.M. Montiel and Juan D. Tardós, University of Zaragoza.
*
* ORB-SLAM3 is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ORB-SLAM3 is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
* the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with ORB-SLAM3.
* If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef VIEWER_H
#define VIEWER_H

#include "FrameDrawer.h"
#include "MapDrawer.h"
#include "Tracking.h"
#include "System.h"
#include "Settings.h"

#include <mutex>

namespace ORB_SLAM3
{

class Tracking;
class FrameDrawer;
class MapDrawer;
class System;
class Settings;

class Viewer
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Viewer(System* pSystem, FrameDrawer* pFrameDrawer, MapDrawer* pMapDrawer, Tracking *pTracking, const string &strSettingPath, Settings* settings);

    void newParameterLoader(Settings* settings);

    // Main thread function. Draw points, keyframes, the current camera pose and the last processed
    // frame. Drawing is refreshed according to the camera fps. We use Pangolin.
    // Note: deprecated due to coredump when running on macos
    // Now: first call SLAM.CreatePanelToViewer(); the last call follows in loop:
    /*
        if (SLAM.RefreshViewerWithCheckFinish()) {
              SLAM.SetViewerFinish();
              break;
        }
    */
    void Run();

    void RequestFinish();

    void RequestStop();

    bool isFinished();

    bool isStopped();

    bool isStepByStep();

    void Release();

    //void SetTrackingPause();
    void SetFinish();
    void CreatePanel();
    bool RefreshWithCheckFinish();

    bool both;
private:

    bool ParseViewerParamFile(cv::FileStorage &fSettings);

    bool Stop();

    System* mpSystem;
    FrameDrawer* mpFrameDrawer;
    MapDrawer* mpMapDrawer;
    Tracking* mpTracker;

    // 1/fps in ms
    double mT;
    float mImageWidth, mImageHeight;
    float mImageViewerScale;

    float mViewpointX, mViewpointY, mViewpointZ, mViewpointF;

    bool CheckFinish();

    bool mbFinishRequested;
    bool mbFinished;
    std::mutex mMutexFinish;

    std::mutex mMutexRun;

    bool mbStopped;
    bool mbStopRequested;
    std::mutex mMutexStop;

    bool mbStopTrack;

    // fix macos visualization
    std::unique_ptr<pangolin::Var<bool>> menuFollowCamera;
    std::unique_ptr<pangolin::Var<bool>> menuCamView;
    std::unique_ptr<pangolin::Var<bool>> menuTopView;
    // pangolin::Var<bool> menuSideView("menu.Side View",false,false);
    std::unique_ptr<pangolin::Var<bool>> menuShowPoints;
    std::unique_ptr<pangolin::Var<bool>> menuShowKeyFrames;
    std::unique_ptr<pangolin::Var<bool>> menuShowGraph;
    std::unique_ptr<pangolin::Var<bool>> menuShowInertialGraph;
    std::unique_ptr<pangolin::Var<bool>> menuLocalizationMode;
    std::unique_ptr<pangolin::Var<bool>> menuReset;
    std::unique_ptr<pangolin::Var<bool>> menuStop;
    std::unique_ptr<pangolin::Var<bool>> menuStepByStep;  // false, true
    std::unique_ptr<pangolin::Var<bool>> menuStep;
    std::unique_ptr<pangolin::Var<bool>> menuShowOptLba;

    std::unique_ptr<pangolin::OpenGlRenderState> s_cam;
    std::unique_ptr<pangolin::View> d_cam;

    pangolin::OpenGlMatrix Twc, Twr;
    pangolin::OpenGlMatrix Ow; // Oriented with g in the z axis
    pangolin::OpenGlMatrix Twwp; // Oriented with g in the z axis, but y and x from camera


    bool bFollow = true;
    bool bLocalizationMode = false;
    bool bStepByStep = false;
    bool bCameraView = true;
    // fix macos visualization
};

}


#endif // VIEWER_H
	

