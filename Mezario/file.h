#pragma once

#include <string>

enum FILE_OPTIONS { PLAYER_NAME, PLAYER_HIGHSCORE, PLAYER_LEVEL, PLAYER_REACHED_LEVEL };

class File {
private:
	static std::string filepath;
	std::string read_file(const std::string search);
	std::string tidy(const std::string dirty);
	void update_key(const std::string key, const std::string value);

public:
	File(const std::string filepath);

	std::string get_name_of_player();
	std::string get_highscore_of_player();
	int get_current_level();
	int get_reached_level();

	void write_file(const FILE_OPTIONS key, std::string value);

	void update_highscore(std::string new_highscore);
	void update_level(int new_level);
	void update_reached_level(int new_level);

	bool file_exists();
};