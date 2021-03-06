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
//--------------------------------------------------------------------------
//
//  Copyright (C)	2018 Matthias Lutz
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
//--------------------------------------------------------------------------

#include "CommunicationTask.hh"
#include "ComponentSkillInterface.hh"

#include <QtCore>


#include <iostream>

CommunicationTask::CommunicationTask(SmartACE::SmartComponent *comp) 
:	CommunicationTaskCore(comp)
{
	std::cout << "constructor CommunicationTask\n";
}
CommunicationTask::~CommunicationTask() 
{
	std::cout << "destructor CommunicationTask\n";
}

///////////////////////////////////////////////////////////////////////////////////////
// trim from start
static inline std::string &ltrim(std::string &s) {
#if defined (__GNUC__) && defined(__unix__)
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
#elif defined (WIN32) || defined (WIN64)
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(isspace))));
#endif
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
#if defined (__GNUC__) && defined(__unix__)
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
#elif defined (WIN32) || defined (WIN64)
	s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), s.end());
#endif
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
	return ltrim(rtrim(s));
}
//
///////////////////////////////////////////////////////////////////////////////////////


int CommunicationTask::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further

	std::string message;
	CommBasicObjects::CommKBRequest request;
	CommBasicObjects::CommKBResponse answer;

	////////////////////////////////////////////////////////////////////
	std::cout<<std::endl<<"[ReadCommandTask] Ready to receive data from FleetManager\n"<<std::endl;
	message = "(defun format-locations-json (s obj colonmod at-sign) (declare (ignore colonmod)) (declare (ignore at-sign)) (format s \"((position-id . ~s) (x . ~3$) (y . ~3$) (phi . ~d) (type . ~s))\" (get-value obj 'name)(/ (first (get-value obj 'approach-region-pose)) 1000) (/ (second (get-value obj 'approach-region-pose)) 1000) (second (get-value obj 'orientation-region)) (get-value obj 'type)))";
	request.setRequest(message);
	std::cout<<"Initial QUERY to KB to propagate the format function for the locations"<<std::endl;
	COMP->kBQueryClient->query(request,answer);
	std::cout<<"Got KB Query Answer: "<<answer.getResponse()<<std::endl;
	////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////
	// JSON
	message = "(defun format-robots-json (s obj colonmod at-sign) (declare (ignore colonmod)) (declare (ignore at-sign)) (format s \"((robot-id . ~d))\" (get-value obj 'name)))";
	request.setRequest(message);
	std::cout<<"Initial QUERY to KB to propagate the format function for the robots id"<<std::endl;
	COMP->kBQueryClient->query(request,answer);
	std::cout<<"Got KB Query Answer: "<<answer.getResponse()<<std::endl;
	////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////
	// JSON
	message = "(defun format-stations-json (s obj colonmod at-sign) (declare (ignore colonmod)) (declare (ignore at-sign)) (format s \"( (station-id . ~s) (x . ~3$) (y . ~3$)  (phi . ~d) (num-belts . ~d) (station-type . ~s) (docking-type . ~s) (approach-location . ~d))\" (get-value obj 'id) (first (get-value obj 'pose)) (second (get-value obj 'pose)) (third (get-value obj 'pose)) (get-value obj 'belt-count) (get-value obj 'type) (get-value obj 'docking-type) (get-value obj 'approach-location) ))";
	request.setRequest(message);
	std::cout<<"Initial QUERY to KB to propagate the format function for the stations"<<std::endl;
	COMP->kBQueryClient->query(request,answer);
	std::cout<<"Got KB Query Answer: "<<answer.getResponse()<<std::endl;
	////////////////////////////////////////////////////////////////////

	std::cout<<std::endl<<"[CommunicationTask] Ready to receive data!\n"<<std::endl;

	return 0;
}


int CommunicationTask::on_execute()
{
	
	std::deque<std::string> mydeque,other,query;
	int retval = COMP->com->recv_lines(mydeque);

	if(retval == 0){

		int ret = separateQuery(mydeque, other, query);

		std::deque<std::string>::iterator it;
		for(it=query.begin(); it!=query.end();++it)
		{
			CommBasicObjects::CommKBRequest request;
			CommBasicObjects::CommKBResponse answer;
			request.setRequest(*it);
			std::cout<<"Query for KB..."<<std::endl;
			Smart::StatusCode status = COMP->kBQueryClient->query(request,answer);
			std::cout<<"... got answer!"<<std::endl;
			if(status == Smart::SMART_OK){
				std::string answerString(answer.getResponse());

				std::cout<<"KB Answer: "<<answerString<<std::endl;
				try{
					if(answerString.compare("NIL") == 0)
					{
						std::cout<<"Got NIL as answer! --> send empty answer string!"<<std::endl;
						answerString = "";
					} else {
						//remove none content chars
						answerString.erase(std::remove_if(answerString.begin(),answerString.end(),
								[] (const char& c) {
									switch(c)
									{
									case '\\':
										return true;
									default:
										return false;
									}}),answerString.end());
						ltrim(answerString); //remove leading blanks
						answerString.erase(0,1); //remove front \"
						answerString.erase(answerString.size()-1,1); //remove tail \"
					}
				} catch (const std::exception& ex) {
					std::cout<<"exception std::exception: "<<ex.what()<<std::endl;
					answerString = "";
				} catch (const std::string& ex) {
					std::cout<<"exception std::string: "<<ex<<std::endl;
					answerString = "";
				} catch (...) {
					std::cout<<"exception ... "<<std::endl;
					answerString = "";
				}

				COMP->com->send(answerString + "\n");
			} else {
				std::cout<<"ERROR - query KB: "<<Smart::StatusCodeConversion(status)<<std::endl;

				if(status == Smart::SMART_DISCONNECTED){
					//this should never had happened!
					status = COMP->kBQueryClient->connect(COMP->connections.kBQueryClient.serverName, COMP->connections.kBQueryClient.serviceName);
					std::cout<<"Reconnect of kbQuery: "<<Smart::StatusCodeConversion(status)<<std::endl;
				}
			}
		}

		for(it=other.begin(); it!=other.end();++it)
		{
			COMP->skillExecutionTask->pushMsg(*it);
		}

	} else if( retval == -1){
		std::cout<<"ERROR from recv!"<<std::endl;
	} else if (retval == 1){
		//timeout --> ok
	}


	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}


int CommunicationTask::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}

int CommunicationTask::separateQuery(std::deque <std::string> &in, std::deque <std::string> &other, std::deque <std::string> &query)
{

	ParameterStateStruct localstate = COMP->getGlobalState();

	//line by line
	for(std::deque<std::string>::iterator it=in.begin(); it!=in.end();)
	{
		QJsonParseError error;
		//QJsonParseError *error;
//		std::cout<<__FUNCTION__<<": in item: "<<*it<<std::endl;
		QString line = QString::fromUtf8(it->c_str());
//		std::cout<<"line: "<<line.toStdString()<<std::endl;
		QJsonDocument doc = QJsonDocument::fromJson(line.toUtf8(),&error);

		if(QJsonParseError::NoError != error.error)
		{
			std::cout<< "error: parsing json error:" << error.errorString().toStdString()<<std::endl;
			it++;
			continue;
		}

		QJsonObject root = doc.object();

		QString msgType = root["msg-type"].toString();
		if(msgType == "query")
		{
			QJsonObject jsonMSG = root["query"].toObject();
			QString queryType = jsonMSG["type"].toString();

			//handeled by jobdispatcher
			//{ "msg-type" : "query" , "query" :  { "type" : "get-robot-id-master-master-components-run-on" }}
			//if(queryType == "get-robot-id-master-master-components-run-on") {}

			//{ "msg-type" : "query" , "query" :  { "type" : "get-all-positions" }}
			if (queryType == "get-all-positions") {
				std::cout<<"get-all-positions"<<std::endl;
				query.push_back("(let ((obj-list     (kb-query-all :key '(is-a) :value '((is-a location))))) (encode-msg (read-from-string (format NIL \"( (msg-type . query-response) (response . ((type . get-all-positions) (positions . (~{~/format-locations-json/~^ ~})))))\" obj-list))))");

				//remove msg from input dequee
				it = in.erase(it);
			}

			/////////////////////////////
			//J O B  Q U E R Y

			else {
				std::cout<<"Error unkown query type, keep: "<< *it <<std::endl;
				++it;
			}

		} else {
			//std::cout<<"Other msg type found --> skip"<<std::endl;
			++it;
		}
	}


	std::deque<std::string>::iterator it;
	for(it=in.begin(); it!=in.end();++it)
	{
		//everything not a query is a command/job/etc.
		other.push_back(*it);
	}

	return 0;
}
