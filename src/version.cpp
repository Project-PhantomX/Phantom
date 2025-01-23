// Luanti
// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright (C) 2013 celeron55, Perttu Ahola <celeron55@gmail.com>

#include "version.h"
#include "config.h"

#if USE_CMAKE_CONFIG_H
	#include "cmake_config_githash.h"
#endif

#ifndef VERSION_GITHASH
	#define VERSION_GITHASH VERSION_STRING
#endif

#define STRINGIFY(x) #x
#define STR(x) STRINGIFY(x)

std::string getVersionHash(int length) {
	const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	std::string randomString;

	// Seed the random number generator
	static bool seeded = false;
	if (!seeded) {
		std::srand(static_cast<unsigned int>(std::time(0)));
		seeded = true;
	}

	for (int i = 0; i < length; ++i) {
		// Generate a random index to select a character from the characters string
		int randomIndex = std::rand() % characters.size();
		randomString += characters[randomIndex];
	}

	return randomString;
}
const char *g_version_string = VERSION_STRING;
const char *g_version_hash = (getVersionHash(7)).c_str();
const char *g_build_info =
	"BUILD_TYPE=" BUILD_TYPE "\n"
	"RUN_IN_PLACE=" STR(RUN_IN_PLACE) "\n"
	"USE_CURL=" STR(USE_CURL) "\n"
#if CHECK_CLIENT_BUILD()
	"USE_GETTEXT=" STR(USE_GETTEXT) "\n"
	"USE_SOUND=" STR(USE_SOUND) "\n"
#endif
	"STATIC_SHAREDIR=" STR(STATIC_SHAREDIR)
#if USE_GETTEXT && defined(STATIC_LOCALEDIR)
	"\n" "STATIC_LOCALEDIR=" STR(STATIC_LOCALEDIR)
#endif
;
