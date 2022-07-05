#include "file.h"

#include <fstream>
#include <iostream>

std::string File::filepath;

File::File(const std::string filepath) 
{
	this->filepath = filepath;
}

std::string File::read_file(const std::string search)
{
	std::ifstream information(this->filepath);

	for (std::string line; getline(information, line); )
	{
		std::string delimiter = ":";
		std::string key = line.substr(0, line.find(delimiter));

		if (search == key) {
			return line;
		}
	}

	// will not happen since every position is always filled in info.mezario
	return "ERROR";
}

void File::write_file(const FILE_OPTIONS key, std::string value)
{
	if (!file_exists()) {
		// creating file, where filepath = filename
		std::ofstream outfile(filepath);
		outfile.close();
	}

	std::ofstream information;
	information.open(filepath, std::ios_base::app);

	if (key == PLAYER_NAME) {
		information << "player.name:";
	} else if (key == PLAYER_HIGHSCORE) {
		information << "player.highscore:";
	}

	information << value << "\n";
}

bool File::file_exists()
{
	std::ifstream infile(this->filepath);
	return infile.good();
}

std::string File::tidy(const std::string dirty)
{
	size_t position = dirty.find(":");
	return dirty.substr(position + 1);
}

std::string File::get_name_of_player() {
	std::string saved = read_file("player.name");
	return tidy(saved);
}

std::string File::get_highscore_of_player() {
	std::string saved = read_file("player.highscore");
	return tidy(saved);
}
