#ifndef _CORE_H_
#define _CORE_H_

#include <systemc.h>
#include <vector>
#include "constants.h"

using namespace std;

SC_MODULE(Core){
	// Core inputs
	sc_in<bool> clk;
	sc_in<bool> start;
	sc_in<bool> channel_available;
	sc_in< sc_uint<CHANNEL_WIDITH> > data_in;

	// Core outputs
	// sc_out< sc_uint<CORE_ID> > requested_CoreId;
	sc_out<int> requested_CoreId;
	sc_out< sc_uint<CHANNEL_WIDITH> > data_out;
	sc_out<bool> thread_finished;

	// Messages
	sc_time cyclesElapsed;
	vector<int> idleCycles; // Waiting time (clock cycles) to request a new communication
	// vector< sc_uint<CORE_ID> > destinyCores; // List of destiny cores to send the packages
	vector<int> destinyCores; // List of destiny cores to send the packages
	vector<int> numPckgs; // Number of packages to be send in each communication
	vector< sc_uint<CHANNEL_WIDITH> > packages; // List of packages to be send from this core.

	// Behaviors
	void requestRoute();

	SC_CTOR(Core):
		clk("noc_clock"),
		start("start"),
		channel_available("channel_available"),
		data_in("data_in"),
		requested_CoreId("requested_CoreId"),
		data_out("data_out"),
		thread_finished("thread_finished")
	{
		cyclesElapsed = sc_time_stamp();

		SC_CTHREAD(requestRoute, clk.pos());
	}
};

#endif