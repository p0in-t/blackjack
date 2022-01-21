#pragma once
#include <Windows.h>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <stdlib.h>
#include <limits>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <direct.h>
#include <cmath>
#include <math.h>
#include "utilities.h"

#define PI 3.14

enum GameStates
{
	STATE_NONE = 0,
	STATE_PRE = 1,
	STATE_BET = 2,
	STATE_IN = 3,
	STATE_END = 4,
};