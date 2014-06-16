#ifndef RES_PATH_H
#define RES_PATH_H

#include <iostream>
#include <string>
#include <SDL.h>

/*
 * Get the resource path for resources located in res/sub_dir
 * It's assumed the project directory is structured like:
 * bin/
 *  the executable
 * res/
 *  Lesson1/
 *  Lesson2/
 *
 * Paths returned will be Project_Root/res/sub_dir
 */
std::string getResourcePath(const std::string &sub_dir = ""){
#ifdef _WIN32
	const char PATH_SEP = '\\';
#else
	const char PATH_SEP = '/';
#endif
	static std::string base_res;
	if (base_res.empty()){
		char *base_path = SDL_GetBasePath();
		if (base_path){
			base_res = base_path;
			SDL_free(base_path);
		}
		else {
			std::cerr << "Error getting resource path: " << SDL_GetError() << std::endl;
			return "";
		}
		//We replace the last bin/ with res/ to get the the resource path
		size_t pos = base_res.find_last_of("bin") - 2;
		base_res = base_res.substr(0, pos) + "res" + PATH_SEP;
	}
	return sub_dir.empty() ? base_res : base_res + sub_dir + PATH_SEP;
}

#endif

