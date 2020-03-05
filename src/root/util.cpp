#include "util.hpp"

#include <utility>

namespace fs = std::filesystem;

namespace {

fs::path _dataPath;

} // namespace

const std::filesystem::path& dataPath()
{
    return _dataPath;
}

void dataPath(std::filesystem::path path)
{
    _dataPath = std::move(path);
}
