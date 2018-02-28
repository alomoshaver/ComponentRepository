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
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------
#include "NavVelInUpcallManager.hh"

NavVelInUpcallManager::NavVelInUpcallManager(
	Smart::InputSubject<CommBasicObjects::CommNavigationVelocity> *subject,
	const int &prescaleFactor)
	:	Smart::IInputHandler<CommBasicObjects::CommNavigationVelocity>(subject, prescaleFactor)
{  }
NavVelInUpcallManager::~NavVelInUpcallManager()
{  }

void NavVelInUpcallManager::notify_upcalls(const CommBasicObjects::CommNavigationVelocity &input)
{
	for(auto it=upcalls.begin(); it!=upcalls.end(); it++) {
		(*it)->on_NavVelIn(input);
	}
}

void NavVelInUpcallManager::attach(NavVelInUpcallInterface *upcall)
{
	upcalls.push_back(upcall);
}
void NavVelInUpcallManager::detach(NavVelInUpcallInterface *upcall)
{
	upcalls.remove(upcall);
}