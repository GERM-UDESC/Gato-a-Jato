

class driver{

  public:

  void driver()
  void ~driver()

  private:

  void GPIO_PinConfig(port, pin, mode) 	//Configure pins as input / output / alternated function
  bool GPIO_PinRead(port, pin)			//read the value of a pin configured as digital input
  void GPIO_PinWrite(port, pin, value)	//write a value in a pin configured as digital output

  int AnalogRead(port,pin)				//read the value of a pin configured as input analog
  void PWM(port,pin, frequency)			//set a PWM signal at a pin 

  void Configure_Timer(port, pin, mode) 	//Configure a timer
  long double Count_Encoder_Pulses(port, pin)	  	//Return the value of pulses readed by encoder
}

