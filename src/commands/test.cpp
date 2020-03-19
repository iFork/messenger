#include "commands.hpp"


int main()
{
	//gui creates msg out request
	cmd_msg_out_request msg_out1(12, "12:30", "Hello msg out request");
	//stringify to send 
	std::stringstream ss1;
	msg_out1.dressed_stringify(ss1);
	std::cout << "ss1: " <<  ss1.str() << std::endl;
		
	//server recives request into buffer and calls command factory
	command* cmd_in1 = command::create(1, ss1.str());
	
	//call overridden virtual methods
	std::stringstream ss2;
	cmd_in1->dressed_stringify(ss2);
	std::cout << "ss2: " <<  ss2.str() << std::endl;

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
		
	

	return 0;
}
