#pragma once

#include "array.h"
#include "list.h"
#include "station.h"

class Application
{

public:

	Application();

	void mainMenu();
	void workMenu();

	int appArray();
	int appList();
	int appStation();
};