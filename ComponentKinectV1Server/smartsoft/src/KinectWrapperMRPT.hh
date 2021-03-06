//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain Version 2.2
// The SmartSoft Toolchain has been developed by:
//
// Christian Schlegel (schlegel@hs-ulm.de)
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// This file is generated once. Modify this file to your needs.
// If you want the toolchain to re-generate this file, please
// delete it before running the code generator.
//--------------------------------------------------------------------------
// --------------------------------------------------------------------------
//
//  Copyright (C) 2011, 2017 Matthias Lutz, Dennis Stampfer, Matthias Rollenhagen, Nayabrasul Shaik
//
//      lutz@hs-ulm.de
//      stampfer@hs-ulm.de
//      rollenhagen@hs-ulm.de
//      shaik@hs-ulm.de
//
//      ZAFH Servicerobotic Ulm
//      Christian Schlegel
//      University of Applied Sciences
//      Prittwitzstr. 10
//      89075 Ulm
//      Germany
//
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2.1
//  of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  General Public License for more details.
//
//  You should have received a copy of the GNU General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//--------------------------------------------------------------------------


#ifndef KINECTWRAPPER_HH_
#define KINECTWRAPPER_HH_

#include <iostream>
#include <stdint.h>
#include <math.h>
#include <vector>

#include "ImageTaskCore.hh"

#include <mrpt/vision/CUndistortMap.h>

#include <MyCKinect.hh>

using namespace mrpt;
using namespace mrpt::hwdrivers;
using namespace mrpt::math;
using namespace mrpt::gui;
//using namespace mrpt::slam;
using namespace mrpt::utils;
using namespace std;


#include "DomainVision/CommRGBDImage.hh"

class KinectWrapper {

private:
	unsigned int imageCounter;

	arma::mat color_intrinsics;
	arma::mat color_distortion;

	arma::mat depth_intrinsics;
	arma::mat depth_distortion;
	arma::mat depth_extrinsics;

	MyCKinect kinect;

	mrpt::vision::CUndistortMap undistort_map;

public:
	KinectWrapper();

	virtual ~KinectWrapper();

	void start_rgb_depth();
	void stop_rgb_depth();
	void get_rgbd_image(DomainVision::CommRGBDImage& image);
	void get_depth_image(DomainVision::CommDepthImage& comm_depth_image, CMatrixFloat& range2D);
	void get_video_image(DomainVision::CommVideoImage& comm_video_image, CImage& intensity_image);
	void read_parameters();
	void print_parameters();

};

#endif /* KINECTWRAPPER_HH_ */
