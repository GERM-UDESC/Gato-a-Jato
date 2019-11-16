#ifndef FOLLOWING_CONTROLER_H
#define FOLLOWING_CONTROLER_H

#include "KINEMATIC_CONTROL.h"
#include "math.h"

//Parameters
//Kanayama
#define Kx 60
#define Ky 1200
#define Kteta 24
	
//artigo
#define K1a 25
#define K2a 1000

#define K4 400
#define K1 Kx
#define K2 Ky
#define K3 Kz
#define alpha 10

#define Kxk 1
#define Kyk 200
#define Ktetak 0.01
#define K4k 0.001


#define v_ref_ini 1.3
#define w_ref_ini 0

class Controller
{
	private:
		static Controller *ptController;
		void Handler();
	
		float xPosLine{0};
		float yPosLine{0};
	
		float xe{0};
		float ye{0};
		float tetae{0};
		float xep{0};
		float yep{0};
		float tetaep{0};
		float lastTetae{0};
		
		float v_ref{v_ref_ini};
		float desired_v{v_ref_ini};
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
		void article_control_v2();
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
		
		float getXline();
		float getYline();
	
		void start(float vr, float wr);
		void stop();
		
};

#endif