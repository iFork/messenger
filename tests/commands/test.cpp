#include "commands.hpp"


/*
Pseudo-code for managing command exchanges between clinet/gui and server

initiating command exchange
	//from gui
	cmd_named_ctor()
	named_cmd->dress();
	named_cmd.stringify(ss);
	gui.client.send(ss);

	//from server - pushing to the client without the client's request
	cmd_named_ctor() 
	named_cmd->dress();
	named_cmd.stringify(ss);
	server.send(user, ss);
	
request-process-response <-> response-process-request loop
	//from server, server recieved a command into its boofer
	gen_request* = request_factory();
	gen_response* = gen_request->process();
	//if command is not terminal
		gen_response->dress();
		gen_response->stringify(ss);
		server.send(ss);
	//if command is terminal
			//rarely response will be terminal at server end !!
			//but may be sign_out_request will not generate sign_out_response
			//but may generate terminal_response
			//where m_cmd_val may be nullptr and it cannot be dressed
		gen_response->dress(); //will do nothing
		gen_response->stringify(ss); //will give ""
		server.send(ss); //check if ss is not "" - send
	
	//from gui, clinet received response into its buffer
	gen_response* = resquest_factory();
	gen_request* = gen_response->process();
	//if not terminal
			//rarely response will be not terminal and will 
			//rarely generate request to send\
			//some cases may be - msg_in_response->process() may 
			//generate back_notification_request();
		gen_request->dress();
		gen_request->stringify(ss);
		server.send(ss);
	//if terminal
			//basic case is terminal
		gen_response->dress(); //will do nothing
		gen_response->stringify(ss); //will give ""
		clinet.send(ss); //check if ss is not "" - send

*/

	
/*

	//NOTE: Alternative to cmd_terminal may be using nullptr and always doing 
	//nullptr check before prepping result of process()

	if (cmd == nullptr) {
		//do not prep
		//do not send
	}
	else {
		//dress
		//stringify
		//send
	}
*/	

using namespace messenger::commands;

void signup_testrun_verbose()
{


	//Signup request - response
	std::cout << "Signup Request Test\n";

	//signup request creation from gui
	cmd_signup_request ut_sgnup_rqst_gui_1("billG");
	std::stringstream signup_sstream;
	ut_sgnup_rqst_gui_1.stringify(signup_sstream);
	std::cout << "ut_sgnup_rqst_gui_1 original: " <<  signup_sstream.str() << std::endl;
	//prepare to send 
	ut_sgnup_rqst_gui_1.dress();
	signup_sstream.str("");
	ut_sgnup_rqst_gui_1.stringify(signup_sstream);
	std::cout << "ut_sgnup_rqst_gui_1 dressed: " <<  signup_sstream.str() << std::endl;
	//send
	//client.send(signup_sstream);	

	//server recives request into buffer and calls command factory
	command* ut_sgnup_rqst_srvr_1 = command::request_factory("", signup_sstream.str()); 
				//user_id is "" for not logged in user
	
	signup_sstream.str("");
	ut_sgnup_rqst_srvr_1->stringify(signup_sstream);
	std::cout << "ut_sgnup_rqst_srvr_1 original: " <<  signup_sstream.str() << std::endl;
	//process
	std::cout<< "Processing signup request recieved at server\n";
	command* ut_sgnup_rspns_srvr_1 = ut_sgnup_rqst_srvr_1->process();
	//delete processed request
	delete ut_sgnup_rqst_srvr_1;
	//prepare response of processing for sending
	ut_sgnup_rspns_srvr_1->dress();
	signup_sstream.str("");
	ut_sgnup_rspns_srvr_1->stringify(signup_sstream);
	std::cout << "ut_sgnup_rspns_srvr_1 is: " <<  signup_sstream.str() << std::endl;
	//send
	//server.send(ss3); 
		//all this is inside a single connection, 
		//connection socket is known for the server
	//delete sent response 	
	delete ut_sgnup_rspns_srvr_1;

	//client receives signup response
	command* ut_sgnup_rspns_gui_1 = command::response_factory(signup_sstream.str());
	//process
	std::cout<< "Processing signup response recieved at client\n";
	//NOTE: process() returns command pointer which, in general should be sent back
	//but in this case returned command is of terminal type, i.e.
	//sending back is not needed, but we follow general prepping steps
	//as we don't know whether we have terminal command or not
	command* ut_terminal_gui_1 = ut_sgnup_rspns_gui_1->process();
	//delete processed response
	delete ut_sgnup_rspns_gui_1;
	//prepare request resulted from response processing for sending
	ut_terminal_gui_1->dress();
	signup_sstream.str("");
	ut_terminal_gui_1->stringify(signup_sstream);
	std::cout << "ut_terminal_gui_1 is: " <<  signup_sstream.str() << std::endl;
	//send, here clinet should not send anything as signup_sstream == ""
	//server.send(ss3); 
	//delete sent request (but in this case it was terminal cmd)
	delete ut_terminal_gui_1;

}

int main()
{

	
	signup_testrun_verbose();
	return 0;
}

void send_msg_testrun_verbose()
{
	//gui creates msg out request
	cmd_msg_out_request msg_out1(12, "12:30", "Hello msg out request");
	//stringify to send 
	std::stringstream ss1;
	msg_out1.stringify(ss1);
	std::cout << "ss1 original: " <<  ss1.str() << std::endl;
	msg_out1.dress();
	ss1.str("");
	msg_out1.stringify(ss1);
	std::cout << "ss1 dressed: " <<  ss1.str() << std::endl;
		
	//server recives request into buffer and calls command factory
	command* cmd_in1 = command::request_factory("johnpi", ss1.str());
	
	//call overridden virtual methods
	std::stringstream ss2;
	cmd_in1->stringify(ss2);
	std::cout << "ss2 original: " <<  ss2.str() << std::endl;
	cmd_in1->strip();
	ss2.str("");
	cmd_in1->stringify(ss2);
	std::cout << "ss2 stripped: " <<  ss2.str() << std::endl;

//	command* cmd_in1_resp = cmd_in1->process();
/*
	//create msg
	msg_out_t msg_out1(12, "12:30", "Hello out 1");
	//parse msg into command
	command_t cmd_msg_out1(msg_out1);
	//stringify command into ss
	std::stringstream ss;
	cmd_msg_out1.stringify(ss);
	std::cout << "ss     is: " << ss.str() << std::endl;	

	//parse received string into command
	command_t cmd_in1(ss.str());
	//stringify command into ss
	std::stringstream ss2;
	cmd_in1.stringify(ss2);
	std::cout << "ss2 is: "  << ss2.str() << std::endl;	
	
	//parse another string into command
	std::string json1 = "{\"cmd_cat\" : 0, \"cmd_val\" : {\"k1\":\"v1\"}  }";
	std::cout << "json1 is: " << json1 << std::endl;
	command_t cmd_in2(json1);
	std::stringstream ss3;
	cmd_in2.stringify(ss3);
	std::cout << ss3.str() << std::endl;	
*/	
	//process
	//TODO: cmd_in1.process();
		
	

}
