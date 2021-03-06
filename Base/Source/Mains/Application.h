#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "..\\Misc\\DetectMemoryLeak.h"
#include <string>
#include "Vector3.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Update();
	void Exit();

	static bool IsKeyPressed(unsigned short key);
    static bool IsMousePressed(unsigned short key);
    static void GetCursorPos(double *xpos, double *ypos);

	// Stored Window Values
	int cA_WindowHeight, cA_WindowWidth;


	//static ISoundEngine* theSoundEngine;
	//static ISound* Sound_Footstep;

	static bool ExitGame;
private:
	Application();
	~Application();

	//Declare a window object
	StopWatch m_timer;
	double m_dElaspedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;

};

#endif