#ifndef KANAYAMA_CONTROLER_H
#define KANAYAMA_CONTROLER_H

#include "KINEMATIC_CONTROL.h"
#include "math.h"

//Constants
#define Kx 80
#define Ky 1000
#define Kteta 20
#define v_ref 1.1
#define w_ref 0

class Controller
{
	private:
		static Controller *ptController;
		void Handler();
	
		float xe{0};
		float ye{0};
		float tetae{0};
		
		float V{0};
		float w{0};
		
	
	public:
		Kinematic Robot;
	
		Controller(Kinematic Robot);
	
		static void HandlerByTime();
		void setSpeedRef(float vr, float wr);
		void controlRule();
		void reset();
		
};

#endif