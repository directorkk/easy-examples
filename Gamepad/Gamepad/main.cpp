#include <iostream>
#include <thread>
#include <string>

#include <conio.h>

#include "Gamepad.h"

int main(int argc, char **argv)
{
	Gamepad wc;
	wc.CheckDevice();


	while(1){
		std::this_thread::sleep_for(std::chrono::milliseconds(1000/20));
		system("cls");

		// Check devices when user presses 'c' 
		if( _kbhit() ){
			char tmpInput = _getch();
			if( tmpInput == 'c' )
				wc.CheckDevice();
		}

		if(wc.GetDeviceCount() == 0){
			std::cout << "There is no connected controller." << std::endl;
			continue;
		}

		for(unsigned int i=0 ; i<wc.GetDeviceCount() ; i++){
			GamepadState gs = wc.GetState(i);

			std::cout << "<Controller " << i << ">" << std::endl;

			std::cout << "StickL:  " << gs.StickLX << ", " << gs.StickLY << std::endl
				<< "StickR:  " << gs.StickRX << ", " << gs.StickRY << std::endl
				<< "Trigger: " << gs.TriggerL << ", " << gs.TriggerR << std::endl
				<< "DpadU:   " << gs.DpadU << std::endl
				<< "DpadR:   " << gs.DpadR << std::endl
				<< "DpadD:   " << gs.DpadD << std::endl
				<< "DpadL:   " << gs.DpadL << std::endl;			

			for(int i=0 ; i<32 ; i++)
				if(gs.Button[i])
					std::cout << "Button:  " << i << std::endl;

			std::cout << std::endl;
		}
	}

	return 0;
}