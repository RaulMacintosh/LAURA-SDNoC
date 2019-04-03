#include "mux.h"

void Mux::switchGate(){
	if(enable.read() == 1){
		cout << "AQUI" << endl;
		switch(selector.read()){
			case 0:
				output.write(in_0.read());
				break;
			case 1:
				output.write(in_1.read());
				break;
			case 2:
				output.write(in_2.read());
				break;
			default:
				output.write(in_3.read());
		}
	}
}