#pragma once

#include <string>

enum FILE_OPTIONS { PLAYER_NAME, PLAYER_HIGHSCORE };

class File {
private:
	static std::string filepath;
	void read_file();

public:
	File(std::string filepath);

	std::string get_name_of_player();
	std::string get_highscore_of_player();

	void write_file(const FILE_OPTIONS key, std::string value);
	bool file_exists();

};