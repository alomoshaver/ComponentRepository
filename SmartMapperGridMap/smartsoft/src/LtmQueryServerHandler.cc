//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
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
#include "LtmQueryServerHandler.hh"
#include "SmartMapperGridMap.hh"

LtmQueryServerHandler::LtmQueryServerHandler(Smart::IQueryServerPattern<CommNavigationObjects::CommGridMapRequest, CommNavigationObjects::CommGridMap, SmartACE::QueryId>* server)
:	LtmQueryServerHandlerCore(server)
{
	
}

LtmQueryServerHandler::~LtmQueryServerHandler()
{
	
}

void LtmQueryServerHandler::on_update_from(const LtmMapTask* ltmMapTask)
{
	// update triggered from LtmMapTask
	// (use a local mutex here, because this method is called from within the thread of LtmMapTask)
}

void LtmQueryServerHandler::handleQuery(const SmartACE::QueryId &id, const CommNavigationObjects::CommGridMapRequest& request) 
{
	CommNavigationObjects::CommGridMap answer;
	
    std::cout << "LtmMapper QueryServer handleQuery id: " << id << std::endl;
    COMP->LtmLock.acquire();
    answer = (CommNavigationObjects::CommGridMap)(*(COMP->ltmGridMap));
    COMP->LtmLock.release();
	
	this->server->answer(id, answer);
}