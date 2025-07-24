#pragma once

#include <sqlite3.h>
#include <string>
#include <vector>

struct Wormhole {
    std::string from_map;
    std::string to_map;
    double x, y, yaw;
};

class WormholeDB {
public:
    WormholeDB(const std::string& db_path);
    ~WormholeDB();

    bool connect();
    std::vector<Wormhole> getWormholesTo(const std::string& target_map);

private:
    sqlite3* db_;
    std::string db_path_;
};
