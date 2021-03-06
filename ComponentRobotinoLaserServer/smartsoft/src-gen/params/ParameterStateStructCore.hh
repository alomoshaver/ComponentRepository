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
#ifndef _PARAMETERSTATESTRUCTCORE_HH
#define _PARAMETERSTATESTRUCTCORE_HH

#include "aceSmartSoft.hh"

#include <iostream>

// forward declaration (in order to define validateCOMMIT(ParameterStateStruct) which is implemented in derived class)
class ParameterStateStruct;

class ParameterStateStructCore
{
	friend class ParamUpdateHandler;
public:
	
		///////////////////////////////////////////
		// Internal params
		///////////////////////////////////////////
		
		/**
		 * Definition of Parameter RobotinoLaser_ini
		 */
		class RobotinoLaser_iniType 
		{
			friend class ParamUpdateHandler;
		protected:
			/**
			 * here are the member definitions
			 */
			bool activatePushNewest;
			bool activate_safetyEventServer;
			double laserPosX;
			double laserPosY;
			double laserPosZ;
			double laserSafetyDist;
			double laserWarningSafetyDist;
			unsigned int max_range;
			unsigned int min_range;
			unsigned int opening_angle;
			double pitch;
			std::string robotinoAddress;
			double roll;
			bool verbose;
			double yaw;
		
		public:
			// default constructor
			RobotinoLaser_iniType() {
				activatePushNewest = true;
				activate_safetyEventServer = true;
				laserPosX = 170.0;
				laserPosY = 0.0;
				laserPosZ = 150.0;
				laserSafetyDist = 0.3;
				laserWarningSafetyDist = 0.3;
				max_range = 5600;
				min_range = 20;
				opening_angle = 240;
				pitch = 0.0;
				robotinoAddress = "192.168.178.40";
				roll = 0.0;
				verbose = false;
				yaw = 0.0;
			}
		
			/**
			 * here are the public getters
			 */
			inline bool getActivatePushNewest() const { return activatePushNewest; }
			inline bool getActivate_safetyEventServer() const { return activate_safetyEventServer; }
			inline double getLaserPosX() const { return laserPosX; }
			inline double getLaserPosY() const { return laserPosY; }
			inline double getLaserPosZ() const { return laserPosZ; }
			inline double getLaserSafetyDist() const { return laserSafetyDist; }
			inline double getLaserWarningSafetyDist() const { return laserWarningSafetyDist; }
			inline unsigned int getMax_range() const { return max_range; }
			inline unsigned int getMin_range() const { return min_range; }
			inline unsigned int getOpening_angle() const { return opening_angle; }
			inline double getPitch() const { return pitch; }
			inline std::string getRobotinoAddress() const { return robotinoAddress; }
			inline double getRoll() const { return roll; }
			inline bool getVerbose() const { return verbose; }
			inline double getYaw() const { return yaw; }
			
			void to_ostream(std::ostream &os = std::cout) const
			{
				os << "RobotinoLaser_ini(";
				os << "activatePushNewest = " << activatePushNewest << ", ";
				os << "activate_safetyEventServer = " << activate_safetyEventServer << ", ";
				os << "laserPosX = " << laserPosX << ", ";
				os << "laserPosY = " << laserPosY << ", ";
				os << "laserPosZ = " << laserPosZ << ", ";
				os << "laserSafetyDist = " << laserSafetyDist << ", ";
				os << "laserWarningSafetyDist = " << laserWarningSafetyDist << ", ";
				os << "max_range = " << max_range << ", ";
				os << "min_range = " << min_range << ", ";
				os << "opening_angle = " << opening_angle << ", ";
				os << "pitch = " << pitch << ", ";
				os << "robotinoAddress = " << robotinoAddress << ", ";
				os << "roll = " << roll << ", ";
				os << "verbose = " << verbose << ", ";
				os << "yaw = " << yaw << ", ";
				os << ")\n";
			}
			
		}; // end class RobotinoLaser_iniType
		
	
		///////////////////////////////////////////
		// External params
		///////////////////////////////////////////
		
	
		///////////////////////////////////////////
		// Instance params
		///////////////////////////////////////////
		
	
protected:

	// Internal params
	RobotinoLaser_iniType RobotinoLaser_ini;
	
	// External params
	
	// Instance params (encapsulated in a wrapper class for each instantiated parameter repository)
	

	void setContent(const ParameterStateStructCore &commit) {
		// External params
	
	}

	// special trigger method (user upcall) called before updating parameter global state
	virtual SmartACE::ParamResponseType handleCOMMIT(const ParameterStateStruct &commitState) = 0;
public:
	ParameterStateStructCore() {  }
	virtual ~ParameterStateStructCore() {  }
	
	// internal param getters
	RobotinoLaser_iniType getRobotinoLaser_ini() const {
		return RobotinoLaser_ini;
	}
	
	// external param getters
	
	// repo wrapper class getter(s)
	
	// helper method to easily implement output stream in derived classes
	void to_ostream(std::ostream &os = std::cout) const
	{
		// Internal params
		RobotinoLaser_ini.to_ostream(os);
		
		// External params
		
		// Instance params (encapsulated in a wrapper class for each instantiated parameter repository)
	}
};

#endif
