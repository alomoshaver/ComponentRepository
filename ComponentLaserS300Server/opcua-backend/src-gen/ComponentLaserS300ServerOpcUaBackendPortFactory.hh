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

#ifndef COMPONENTLASERS300SERVER_OPC_UA_BACKEND_PORTFACTORY_HH_
#define COMPONENTLASERS300SERVER_OPC_UA_BACKEND_PORTFACTORY_HH_

// include the main component-definition class
#include "ComponentLaserS300ServerPortFactoryInterface.hh"

#include <thread>
#include <chrono>

// include SeRoNetSDK library
#include <SeRoNetSDK/SeRoNet/Utils/Task.hpp>
#include <SeRoNetSDK/SeRoNet/Utils/Component.hpp>

class ComponentLaserS300ServerOpcUaBackendPortFactory: public ComponentLaserS300ServerPortFactoryInterface
{
private:
	// internal component instance
	SeRoNet::Utils::Component *componentImpl;
	
	// component thread
	std::thread component_thread;
	
	// internal component thread method
	int task_execution();
public:
	ComponentLaserS300ServerOpcUaBackendPortFactory();
	virtual ~ComponentLaserS300ServerOpcUaBackendPortFactory();

	virtual void initialize(ComponentLaserS300Server *component, int argc, char* argv[]) override;
	virtual int onStartup() override;

	virtual Smart::IPushClientPattern<CommBasicObjects::CommBaseState> * createBaseTimedClient() override;
	
	virtual Smart::IPushServerPattern<CommBasicObjects::CommMobileLaserScan> * createLaserPushNewestServer(const std::string &serviceName) override;
	virtual Smart::IQueryServerPattern<CommBasicObjects::CommVoid, CommBasicObjects::CommMobileLaserScan> * createLaserQueryServer(const std::string &serviceName) override;
	virtual Smart::IEventServerPattern<CommBasicObjects::CommLaserSafetyEventParam, CommBasicObjects::CommLaserSafetyField, CommBasicObjects::CommLaserSafetyEventState> * createSafetyfieldEventServer(const std::string &serviceName, std::shared_ptr<Smart::IEventTestHandler<CommBasicObjects::CommLaserSafetyEventParam, CommBasicObjects::CommLaserSafetyField, CommBasicObjects::CommLaserSafetyEventState>> safetyfieldEventServerEventTestHandler) override;
	
	virtual int onShutdown(const std::chrono::steady_clock::duration &timeoutTime=std::chrono::seconds(2)) override;
	virtual void destroy() override;
};

#endif /* COMPONENTLASERS300SERVER_SERONET_SDK_PORTFACTORY_HH_ */
