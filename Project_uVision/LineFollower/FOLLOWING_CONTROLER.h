#ifndef FOLLOWING_CONTROLER_H
#define FOLLOWING_CONTROLER_H

#include "KINEMATIC_CONTROL.h"
#include "math.h"

//Constants
#define Kx 80
#define Ky 1000
#define Kteta 20
#define K4 400
#define K1 Kx
#define K2 Ky
#define K3 Kz
#define v_ref_ini 1
#define w_ref_ini 0

class Controller
{
	private:
		static Controller *ptController;
		void Handler();
	
		float xe{0};
		float ye{0};
		float tetae{0};
		float xep{0};
		float yep{0};
		float tetaep{0};
		
		float v_ref{v_ref_ini};
		float w_ref{w_ref_ini};
		
		float v{0};
		float w{0};
		
		float vc{0};
		float wc{0};
		float vcp{0};
		float wcp{0};
		
		void kanayama_control();
		void fierro_control();
		void article_control();
	
	public:
		Kinematic Robot;
	
		Controller(Kinematic Robot);
	
		static void HandlerByTime();
		void setSpeedRef(float vr, float wr);
		void controlRule();
		void reset();
		
};

#endif