#include <iostream>
#include <string>
#include <fstream>
#include <dirent.h>

int dir(std::string path){
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (path.c_str())) != NULL) {
		
		//print all the files and directories within directory
		while ((ent = readdir (dir)) != NULL) {
			//*
			if (ent->d_name == std::string("."))  { continue; } //REMOVE PWD
			if (ent->d_name == std::string("..")) { continue; } //REMOVE PARENT DIR
			/**/
			
			std::cout << path << "\\" << ent->d_name << std::endl;
		}
		
		closedir (dir);
	}
	else {
		std::cerr << "can't open dir" << std::endl;
		return 1;
	}
	
	return 0;
}

void cp(const char* src, const char* dest){
    char buff[BUFSIZ];
    FILE *in, *out;
    size_t n;
	
    in  = fopen(src,  "rb");
    out = fopen(dest, "wb");
    while ((n = fread(buff, 1, BUFSIZ, in)) != 0) { fwrite(buff, 1, n, out); }
}



int cpDir(std::string sorc, std::string dest){
	
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(sorc.c_str())) != NULL) {
	
		while ((ent = readdir (dir)) != NULL) {
			//*
			if (ent->d_name == std::string("."))  { continue; } //REMOVE PWD
			if (ent->d_name == std::string("..")) { continue; } //REMOVE PARENT DIR
			/**/
			
			std::string copy_sorc = sorc + "\\" + ent->d_name;
			std::string copy_dest = dest + "\\" + ent->d_name;
			std::cout << "cp " << copy_sorc << " -> " << copy_dest << std::endl;
			cp(copy_sorc.c_str(), copy_dest.c_str());
		}
		
		closedir (dir);
	}
	else {
		std::cerr << "can't open dir" << std::endl;
		return 1;
	}
	
	return 0;
}

int main(int argc, char* argv[]){

	// dir();   //print files in dir
	// cp();    //copy file
	// cpDir(); //copy dir
	
	dir(".");
	
	return 0;
}
