#pragma once

#include <string>

enum FILE_OPTIONS { PLAYER_NAME, PLAYER_HIGHSCORE };

class File {
private:
	static std::string filepath;
	std::string read_file(const std::string search);
	std::string tidy(const std::string dirty);

public:
	File(const std::string filepath);

	std::string get_name_of_player();
	std::string get_highscore_of_player();

	void write_file(const FILE_OPTIONS key, std::string value);
	void update_highscore(std::string new_highscore);
	bool file_exists();
};