//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
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
//  Copyright (C) 2008 Christian Schlegel, Andreas Steck, Matthias Lutz
//
//        schlegel@hs-ulm.de
//        steck@hs-ulm.de
//
//        ZAFH Servicerobotik Ulm
//        University of Applied Sciences
//        Prittwitzstr. 10
//        D-89075 Ulm
//        Germany
//
//  This file is part of the "SmartSoft CDL component".
//  It provides navigation services based on the CDL
//  Curvature Distance Lookup approach.
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// --------------------------------------------------------------------------

#include "CompHandler.hh"
#include "SmartCdlServer.hh"

#include <iostream>

// include communication objects
#include <CommNavigationObjects/CommCdlGoalEventParameter.hh>
#include <CommBasicObjects/CommNavigationVelocity.hh>
#include <CommNavigationObjects/CdlGoalEventState.hh>
#include <CommNavigationObjects/CommCdlRobotBlockedEventParameter.hh>
#include <CommNavigationObjects/CommCdlRobotBlockedEventResult.hh>
#include <CommNavigationObjects/CommCdlRobotBlockedState.hh>
#include <CommBasicObjects/CommLaserScan.hh>
#include <CommBasicObjects/CommJoystick.hh>
#include <CommNavigationObjects/CommPlannerGoal.hh>
#include <CommNavigationObjects/CommCdlGoalEventResult.hh>


void CompHandler::onStartup() 
{
	std::cout << "startup - put your startupCode in CompHandler::onStartup()!!!\n";

	Smart::StatusCode status;

    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "| Curvature Distance Lookup Server                                     |\n";
    std::cout << "| ZAFH Servicerobotik Ulm                                              |\n";
    std::cout << "| Copyright (C) 2008 Christian Schlegel, Andreas Steck                 |\n";
    std::cout << "------------------------------------------------------------------------\n\n";

#if DEBUG_CDL_LOOKUP_FILE_OUT
    COMP->cdlLookupdebug.open("/tmp/cdlLookupdebug.txt");
#endif

    // ----------------------------------------------------------
    // global states
    // ----------------------------------------------------------
//    COMP->globalState.lookupTable  	= CommNavigationObjects::CdlTagType::CDL_DEFAULT_LOOKUP;
//    COMP->globalState.strategy     	= CommNavigationObjects::CdlTagType::CDL_NEUTRAL;
//    COMP->globalState.goalSpec     	= CommNavigationObjects::CdlTagType::CDL_NEUTRAL;
//    COMP->globalState.freeBehavior 	= CommNavigationObjects::CdlTagType::CDL_NO_FREE_BEHAVIOR;

    //<alexej>
    /*
    COMP->CDLglobalState.lookupTable  	= CdlTagType::stringToLiteral(COMP->getGlobalState().getLOOKUPTABLE().lookupTable);
    COMP->CDLglobalState.strategy     	= CdlTagType::stringToLiteral(COMP->getGlobalState().getSTRATEGY().strategy);
    COMP->CDLglobalState.goalSpec     	= CdlTagType::stringToLiteral(COMP->getGlobalState().getGOALMODE().goalSpec);
    COMP->CDLglobalState.freeBehavior 	= CdlTagType::stringToLiteral(COMP->getGlobalState().getFREEBEHAVIOR().freeBehavior);

    COMP->CDLglobalState.id           	= COMP->getGlobalState().getID().id;

//    COMP->CDLglobalState.plannerInit  	= COMP->getGlobalState().getSERVER().plannerInit;
//    COMP->CDLglobalState.trackerInit    = COMP->getGlobalState().getSERVER().trackerInit;

    COMP->CDLglobalState.followHysteresis = COMP->getGlobalState().getCDL().folowHysteresis;

    COMP->CDLglobalState.rotateError   = COMP->getGlobalState().getCDLROTATE().error * M_PI/180.0;

    COMP->CDLglobalState.transAcc		= COMP->getGlobalState().getCDL().translation_acc;
    COMP->CDLglobalState.rotAcc			= COMP->getGlobalState().getCDL().rotation_acc * M_PI/180.0;
    COMP->CDLglobalState.ttrigger		= COMP->getGlobalState().getCDL().delta_t_trigger;
    COMP->CDLglobalState.tcalc			= COMP->getGlobalState().getCDL().delta_t_calc;
    COMP->CDLglobalState.vmin			= COMP->getGlobalState().getTRANSVEL().vmin;
    COMP->CDLglobalState.vmax			= COMP->getGlobalState().getTRANSVEL().vmax;
    COMP->CDLglobalState.wmin			= COMP->getGlobalState().getROTVEL().wmin * M_PI/180.0;
    COMP->CDLglobalState.wmax			= COMP->getGlobalState().getROTVEL().wmax * M_PI/180.0;

    COMP->CDLglobalState.goalX         = COMP->getGlobalState().getGOALREGION().goalX;
    COMP->CDLglobalState.goalY         = COMP->getGlobalState().getGOALREGION().goalY;
    COMP->CDLglobalState.goalA         = COMP->getGlobalState().getGOALREGION().goalA;


//    // TODO: seems to be nonfunctional...
//    COMP->globalState.plannerClientSubscribed = false;

    COMP->CdlGlobalLock.release();
    */
    //</alexej>
    COMP->cdlLookup = &(COMP->cdlLookupDefault);
    COMP->cdlLookup->setSafetyClearance(COMP->getGlobalState().getCommNavigationObjects().getCdlParameter().getSAFETYCL().getSafetyClearance());

    COMP->cdlLookupDefault.use_obstacle_history = COMP->getGlobalState().getCdl().getUse_obstacle_history();

    // ----------------------------------------------------------
    // Loding lookup tables
    // ----------------------------------------------------------
    std::cout << "\nLoading lookup tables ...\n";

    std::string temp;
    //THIS HAS TO BE LOADED FIRST!!!!!!
    temp = COMP->getGlobalState().getCdl().getDataDir();
    temp += COMP->getGlobalState().getCdl().getContour_default_file();
    std::cout << "loading " << temp << std::endl;
    if( COMP->cdlLookupDefault.cdl_load_contour_ascii( const_cast<char*>(temp.c_str()) ) != true )
    {
      std::cerr << "Error loading contour default file\n";
      exit(0);
    }

    //THIS HAS to BE DONE SECOND!!!
    COMP->cdlLookupDefault.initLookup(
    		COMP->getGlobalState().getPathNav().getPathNavRecover_max_dist(),
    		COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_minDist(),
    		std::make_pair( COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll2_speed(), COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll1_dist()),
    		std::make_pair( COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll2_speed(), COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll2_dist()),
    		std::make_pair( COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll2_speed(), COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll3_dist())
    );

    temp =  COMP->getGlobalState().getCdl().getDataDir();
    temp += COMP->getGlobalState().getCdl().getCurvature_default_file();
    std::cout << "loading " << temp << std::endl;
    if( COMP->cdlLookupDefault.loadCurvatureIndexAscii( const_cast<char*>(temp.c_str()) ) != 0)
    {
      std::cerr << "Error loading default curvature file\n";
      exit(0);
    }


    if(COMP->getGlobalState().getCdl().getLookup_default_file_compressed() == true){
    	temp = COMP->getGlobalState().getCdl().getDataDir();
		temp += COMP->getGlobalState().getCdl().getLookup_default_file();
		std::cout << "uncompressing " << temp << std::endl;
		std::string uncompressed_filename(temp + ".uncompressed");
    	COMP->cdlLookupDefault.save_file_uncompressed(const_cast<char*>(temp.c_str()), const_cast<char*>(uncompressed_filename.c_str()));
    	std::cout << "loading " << uncompressed_filename << std::endl;
    	if( COMP->cdlLookupDefault.loadDistAngleLookupBin( const_cast<char*>(uncompressed_filename.c_str()) ) != 0 )
		{
		  std::cerr << "Error loading lookup default file " << temp << "\n";
		  exit(0);
		}

    } else {
		temp = COMP->getGlobalState().getCdl().getDataDir();
		temp += COMP->getGlobalState().getCdl().getLookup_default_file();
		std::cout << "loading " << temp << std::endl;
		if( COMP->cdlLookupDefault.loadDistAngleLookupBin( const_cast<char*>(temp.c_str()) ) != 0 )
		{
		  std::cerr << "Error loading lookup default file " << temp << "\n";
		  exit(0);
		}
    }

    temp = COMP->getGlobalState().getCdl().getDataDir();
    temp += COMP->getGlobalState().getCdl().getAccel_default_file();
    std::cout << "loading " << temp << std::endl;
    if( COMP->cdlLookupDefault.loadAccLookupBin( const_cast<char*>(temp.c_str()) ) != 0 )
    {
      std::cerr << "Error loading acceleration default file\n";
      exit(0);
    }

    temp = COMP->getGlobalState().getCdl().getDataDir();
	temp += COMP->getGlobalState().getCdl().getContour_second_file();
	std::cout << "loading " << temp << std::endl;
	if( COMP->cdlLookupSecond.cdl_load_contour_ascii( const_cast<char*>(temp.c_str()) ) != true )
	{
	 std::cerr << "Error loading contour second file\n";
	 exit(0);
	}

	//THIS HAS to BE DONE SECOND!!!
	COMP->cdlLookupSecond.initLookup(
    		COMP->getGlobalState().getPathNav().getPathNavRecover_max_dist(),
    		COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_minDist(),
    		std::make_pair( COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll1_speed(), COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll1_dist()),
    		std::make_pair( COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll2_speed(), COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll2_dist()),
    		std::make_pair( COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll3_speed(), COMP->getGlobalState().getPathNav().getPathNavPredictedGoalPose_controll3_dist())
    );

    temp = COMP->getGlobalState().getCdl().getDataDir();
    temp += COMP->getGlobalState().getCdl().getCurvature_second_file();
    std::cout << "loading " << temp << std::endl;
    if( COMP->cdlLookupSecond.loadCurvatureIndexAscii( const_cast<char*>(temp.c_str()) ) != 0 )
    {
      std::cerr << "Error loading second curvature file\n";
      exit(0);
    }


    if(COMP->getGlobalState().getCdl().getLookup_second_file_compressed() == true){
    	temp = COMP->getGlobalState().getCdl().getDataDir();
		temp += COMP->getGlobalState().getCdl().getLookup_second_file();
		std::cout << "uncompressing " << temp << std::endl;
		std::string uncompressed_filename(temp + ".uncompressed");
    	COMP->cdlLookupSecond.save_file_uncompressed(const_cast<char*>(temp.c_str()), const_cast<char*>(uncompressed_filename.c_str()));
    	std::cout << "loading " << uncompressed_filename << std::endl;
    	if( COMP->cdlLookupSecond.loadDistAngleLookupBin( const_cast<char*>(uncompressed_filename.c_str()) ) != 0 )
		{
		  std::cerr << "Error loading lookup second file " << temp << "\n";
		  exit(0);
		}

    } else {

		temp = COMP->getGlobalState().getCdl().getDataDir();
		temp += COMP->getGlobalState().getCdl().getLookup_second_file();
		std::cout << "loading " << temp << std::endl;
		if( COMP->cdlLookupSecond.loadDistAngleLookupBin( const_cast<char*>(temp.c_str()) ) != 0 )
		{
		  std::cerr << "Error loading lookup second file\n";
		  exit(0);
		}
    }

    temp = COMP->getGlobalState().getCdl().getDataDir();
    temp += COMP->getGlobalState().getCdl().getAccel_second_file();
    std::cout << "loading " << temp << std::endl;
    if( COMP->cdlLookupSecond.loadAccLookupBin( const_cast<char*>(temp.c_str()) ) != 0 )
    {
      std::cerr << "Error loading acceleration second file\n";
      exit(0);
    }





    std::cout << "... lookup tables loaded successfully\n";





	// Start all services. If you need manual control, use the content of this function to
	// connect and start each service individually, e.g:
	// COMP->connectMyPortName("SmartExampleComponent", "examplePort");
//	status = COMP->connectAndStartAllServices();


	status = COMP->connectLaserClient(COMP->connections.laserClient.serverName, COMP->connections.laserClient.serviceName);
	status = COMP->connectNavVelSendClient(COMP->connections.navVelSendClient.serverName, COMP->connections.navVelSendClient.serviceName);

	if(COMP->getGlobalState().getServer().getLaserClient2Init()) {
		status = COMP->connectLaserClient2(COMP->connections.laserClient2.serverName, COMP->connections.laserClient2.serviceName);
	}

	if(COMP->getGlobalState().getServer().getPlannerInit()) {
		status = COMP->connectPlannerClient(COMP->connections.plannerClient.serverName, COMP->connections.plannerClient.serviceName);
	}

	if(COMP->getGlobalState().getServer().getTrackerInit()) {
		status = COMP->connectTrackingClient(COMP->connections.trackingClient.serverName, COMP->connections.trackingClient.serviceName);
	}

	if(COMP->getGlobalState().getServer().getIrClientInit()) {
		status = COMP->connectIRClient(COMP->connections.iRClient.serverName, COMP->connections.iRClient.serviceName);

	}

	if(COMP->getGlobalState().getServer().getPathNavInit()) {
		status = COMP->connectPathNavigationGoalClient(COMP->connections.pathNavigationGoalClient.serverName, COMP->connections.pathNavigationGoalClient.serviceName);

	}

	if(COMP->getGlobalState().getServer().getBaseClientInit()){
		status = COMP->connectBaseStateClient(COMP->connections.baseStateClient.serverName, COMP->connections.baseStateClient.serviceName);
	}


//	// activate state slave
	status = COMP->stateSlave->activate();
	if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
	else std::cout << "STATE SERVER ACTIVATED" << std::endl;

	
	// Start all tasks. If you need manual control, use the content of this function to
	// start each task individually.
	COMP->startAllTasks();
	
	// Start all timers. If you need manual control, use the content of this function to
	// start each timer individually.
	COMP->startAllTimers();
	
	// Notify the component that setup/initialization is finished.
	// You may move this function to any other place.
	COMP->setStartupFinished(); 
}

void CompHandler::onShutdown() 
{
	std::cout << "shutdown - put your cleanup code in CompHandler::onShutdown()!!!\n";
#if DEBUG_CDL_LOOKUP_FILE_OUT
	if(COMP->cdlLookupdebug.is_open()){
		COMP->cdlLookupdebug.open("/tmp/cpdLookupdebug.txt");
		std::cout<<"Closed Lookup debug file!"<<std::endl;
	}
#endif
}
