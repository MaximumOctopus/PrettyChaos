//
// PrettyChaos 1.0
//
// (c) Paul Alan Freshney 2024
//
// paul@freshney.org
//
// https://github.com/MaximumOctopus/PrettyChaos
//

#pragma once

#include <thread>

class MandelbrotRenderCore
{
	static const int __RMEscapeTime = 0;
	static const int __RMContinuous = 1;
	static const int __RMDistance = 2;
	static const int __RMDistanceII = 3;
	static const int __RMOrbitTrap = 4;
	static const int __RMOrbitTrapFilled = 5;
	static const int __RMTwoTone = 6;
	static const int __RMThreeTone = 7;
	static const int __RMFourTone = 8;
	static const int __RMFiveTone = 9;

	int YStart = 0;
	int YEnd = 0;
	int Width = 0;
	int Height = 0;
	double xmin = 0;
	double xmax = 0;
	double ymin = 0;
	double ymax = 0;

	double max_iterations = 1000;
	double bailout_radius = 256;
	int RenderMode = 0;

	void ColourNTone(int);
	void ColourTwoTone();
	void ColourThreeTone();
	void ColourDistanceI(double);
	void ColourDistanceII(double);
	void OrbitTrap(bool);

public:

	std::thread fred;

	int* Iteration = nullptr;

	MandelbrotRenderCore();

	~MandelbrotRenderCore();

	void Render();

	void SetRenderBounds(int, int, int);
	void SetFractalBounds(double, double, double, double);
};
