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
	} else if (key == PLAYER_LEVEL) {
		information << "player.level:";
	}

	information << value << "\n";
}

void File::update_key(const std::string key, const std::string value) {
	std::ifstream information(this->filepath);

	std::ofstream information_new;
	information_new.open("info.mezario.tmp", std::ios_base::app);

	for (std::string line; getline(information, line); )
	{
		std::string delimiter = ":";
		std::string search = line.substr(0, line.find(delimiter));

		if (key != search) {
			information_new << line << "\n";
		}
		else {
			information_new << key << ":" << value << "\n";
		}
	}

	information.close();
	std::remove("info.mezario");

	information_new.close();
	rename("info.mezario.tmp", "info.mezario");
}

void File::update_highscore(std::string new_highscore)
{
	int current_highscore = std::stoi(get_highscore_of_player());
	int new_highscore_int = std::stoi(new_highscore);

	if (current_highscore >= new_highscore_int) {
		// no updating the highscore if it is not a HIGHscore ;)
		return;
	}

	update_key("player.highscore", new_highscore);
}

void File::update_level(int new_level)
{
	if (new_level < 1 || new_level > 5) {
		return;
	}

	update_key("player.level", std::to_string(new_level));
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

int File::get_current_level() {
	std::string saved = read_file("player.level");
	return std::stoi(tidy(saved));
}
