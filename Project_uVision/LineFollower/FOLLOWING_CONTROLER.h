#ifndef FOLLOWING_CONTROLER_H
#define FOLLOWING_CONTROLER_H

#include "KINEMATIC_CONTROL.h"
#include "math.h"

//Parameters
//Kanayama
#define Kx 60
#define Ky 900
#define Kteta 22
#define K4 400
#define K1 Kx
#define K2 Ky
#define K3 Kz

#define Kxk 1
#define Kyk 100
#define Ktetak 0.1
#define K4k 0.01

#define K1a 22
#define K2a 1000

#define v_ref_ini 0.6
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
		float lastTetae{0};
		
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
		void calculateError();
	
	public:
		Kinematic Robot;
	
		Controller(Kinematic Robot);
	
		static void HandlerByTime();
		void setSpeedRef(float vr, float wr);
		void controlRule();
		void reset();
	
		float getVcontrol();
		float getWcontrol();
	
		void start(float vr, float wr);
		void stop();
		
};

#endif