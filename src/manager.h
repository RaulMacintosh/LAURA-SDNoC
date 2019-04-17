#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <systemc.h>
#include <vector>
#include "constants.h"

using namespace std;

SC_MODULE(Manager){
	// Manager inputs
	sc_in<bool> clk;
	sc_in<int> route_requests[N*M];
	sc_in<bool> routing_algorithm;

	// Manager outputs
	sc_out<bool> available_channels[N*M];

	// Messages

	// Behaviors
	void routeRequest();
	void generateRoutes();

	// Graphs
	int network[N*M][N*M];
	vector< vector<int> > paths;

	// Requests queue
	vector<int> requests_queue;

	void dijkstra(int src, int dest);
	void xy(int srcX, int srcY, int destX, int destY);
	void printNetwork();

	SC_CTOR(Manager):
		clk("noc_clock"),
		routing_algorithm("routing_algorithm")
	{

		for(int i = 0; i < N*M; i++){
			for(int j = 0; j < N*M; j++){
				network[i][j] = 0;

				if(i == j){
					network[i][j] = -1;
				}
			}
		}

		for(int i = 0; i < N*M; i++){
			for(int j = i + 1; j < N*M; j++){
				if(i < (N*M - N)){
					if((i+1) % N != 0){
						network[i][j] = 1;
						network[j][i] = 1;

						j += N - 1;

						network[i][j] = 1;
						network[j][i] = 1;

						break;
					}else{
						j += N - 1;

						network[i][j] = 1;
						network[j][i] = 1;
						break;
					}
				}else{
					if(i < (N*M - 1) && (i+1) % N != 0){
						network[i][j] = 1;
						network[j][i] = 1;
						break;
					}
				}
			}
		}

		SC_CTHREAD(routeRequest, clk.pos());
		SC_CTHREAD(generateRoutes, clk.pos());		
	}
};

#endif