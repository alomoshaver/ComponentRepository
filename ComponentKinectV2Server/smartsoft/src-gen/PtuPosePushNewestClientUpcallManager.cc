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
#include "PtuPosePushNewestClientUpcallManager.hh"

PtuPosePushNewestClientUpcallManager::PtuPosePushNewestClientUpcallManager(
	Smart::InputSubject<CommBasicObjects::CommDevicePoseState> *subject,
	const int &prescaleFactor)
	:	Smart::IInputHandler<CommBasicObjects::CommDevicePoseState>(subject, prescaleFactor)
{  }
PtuPosePushNewestClientUpcallManager::~PtuPosePushNewestClientUpcallManager()
{  }

void PtuPosePushNewestClientUpcallManager::notify_upcalls(const CommBasicObjects::CommDevicePoseState &input)
{
	for(auto it=upcalls.begin(); it!=upcalls.end(); it++) {
		(*it)->on_ptuPosePushNewestClient(input);
	}
}

void PtuPosePushNewestClientUpcallManager::attach(PtuPosePushNewestClientUpcallInterface *upcall)
{
	upcalls.push_back(upcall);
}
void PtuPosePushNewestClientUpcallManager::detach(PtuPosePushNewestClientUpcallInterface *upcall)
{
	upcalls.remove(upcall);
}
