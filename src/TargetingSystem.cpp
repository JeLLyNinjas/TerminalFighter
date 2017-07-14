#include "TargetingSystem.h"


TargetingSystem::TargetingSystem(int word_length_lb, int word_length_ub, std::string color_hex)
    : word_length_lb_(word_length_lb)
    , word_length_ub_(word_length_ub)
    , color_hex_(color_hex) {
}

void TargetingSystem::setup_local_dict(std::string relative_path) {

	std::ifstream infile("thefile.txt");
	//local_dict_ is 2D vector. 1st dimension is used to split words on length
	//where index represents word length, 2nd dimension holds the words
	local_dict_.resize(30);

	for (std::string line; std::getline(infile, line); ) {
        if (line.length() < 30){
			local_dict_[line.length()].push_back(line);
		}
	}

	infile.close();
}

std::string TargetingSystem::grab_word(int lb, int ub) {
	int random_word_length = lb + (rand() % (ub-lb));
	return local_dict_[random_word_length].at(rand() % local_dict_[random_word_length].size());
}
