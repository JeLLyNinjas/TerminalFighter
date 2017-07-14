#include "TargetingSystem.h"


TargetingSystem::TargetingSystem(int word_length_lb, int word_length_ub, std::string color_hex)
    : word_length_lb_(word_length_lb)
    , word_length_ub_(word_length_ub)
    , color_hex_(color_hex) {
}

void TargetingSystem::setup_dictionary(std::string relative_path) {

	std::ifstream infile("thefile.txt");
	local_dict_.resize(30);

	for (std::string line; std::getline(infile, line); ) {
        if (line.length() < 30){
			local_dict_[line.length()].push_back(line);
		}
	}

}
