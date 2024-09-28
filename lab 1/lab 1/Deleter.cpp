#include "Deleter.h"

void Deleter::deleteDirs(std::vector<std::pair<std::string, int>> const& dirs)
{
	std::for_each(dirs.cbegin(), dirs.cend(), Deleter::deleteDir);
}

void Deleter::deleteDir(std::pair<std::string, int> const& dir)
{
    auto localRoot = dir.first; 
    auto depth = dir.second;
    if (!fs::exists(localRoot)) {
        syslog(LOG_INFO, "There is no such filepath or it was already removed (%s)", localRoot.c_str());
        return;
    }
    auto it = fs::directory_iterator(localRoot);
    // save the dirs and files at `rootDepth + 1` depth to delete only them,
    // not the moved from the further depth
    std::vector<fs::directory_entry> toRemove(begin(it), end(it));
    try {
        checkForSubdir(localRoot, _rootDepth + 1, depth);
        std::for_each(toRemove.begin(), toRemove.end(), [](const auto& entry) { fs::remove_all(entry.path()); });
    }
    catch (fs::filesystem_error& err) {
        syslog(LOG_ERR, "%s", err.what());
    }
}

void Deleter::checkForSubdir(const fs::path& current_dir, int current_level, int depth)
{
	auto dir_iterator = fs::directory_iterator(current_dir);

    // these files should not be removed, move them under the `currRoot`
    if (current_level > depth) {
        for (const auto& entry : dir_iterator) {
            const auto& path = entry.path();
            auto part = path.end();
            // get the last part of the residual path into `part`
            for (int depth = current_level + 1; depth > _rootDepth + 1; part--, depth--);
            // collect the path from its parts, add the filename of the current entry
            fs::rename(path, std::accumulate(std::next(path.begin()), part, fs::path{}, std::divides{}) /
                path.filename());
        }
    }
    else
        for (const auto& entry : dir_iterator)
            if (entry.is_directory())
                checkForSubdir(entry.path(), current_level + 1, depth);
}