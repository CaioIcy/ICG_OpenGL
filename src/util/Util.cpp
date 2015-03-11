#include "util/Util.h"
#include <sstream>
#include <fstream>
#include "util/Assert.h"

namespace ogle {
namespace util {

std::string FileContentsToString(const std::string& path) {
	std::ifstream file(path);
    std::string file_str{""};

    while(file.good()) {
    	ASSERT(file.bad() != true, "File manipulation error.");

        std::string line{""};
        std::getline(file, line);
        file_str.append(line + "\n");
    }

    file.close();

    return file_str;
}

} // namespace util
} // namespace ogle
