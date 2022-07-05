#include "file.h"

#include <fstream>

std::string File::filepath;

File::File(std::string filepath) 
{
	this->filepath = filepath;
}

void File::read_file()
{

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
	} else (key == PLAYER_HIGHSCORE) {
		information << "player.highscore:";
	}

	information << value << "\n";
}

bool File::file_exists()
{
	std::ifstream infile(this->filepath);
	return infile.good();
}
