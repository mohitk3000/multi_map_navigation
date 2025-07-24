#include "multi_map_nav/wormhole_db.hpp"
#include <iostream>

WormholeDB::WormholeDB(const std::string& path) : db_(nullptr), db_path_(path) {}
WormholeDB::~WormholeDB() { if (db_) sqlite3_close(db_); }

bool WormholeDB::connect() {
    return sqlite3_open(db_path_.c_str(), &db_) == SQLITE_OK;
}

std::vector<Wormhole> WormholeDB::getWormholesTo(const std::string& target_map) {
    std::vector<Wormhole> results;
    std::string query = "SELECT from_map, to_map, position_x, position_y, orientation FROM wormholes WHERE to_map = '" + target_map + "';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            Wormhole w;
            w.from_map = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            w.to_map   = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            w.x        = sqlite3_column_double(stmt, 2);
            w.y        = sqlite3_column_double(stmt, 3);
            w.yaw      = sqlite3_column_double(stmt, 4);
            results.push_back(w);
        }
    }
    sqlite3_finalize(stmt);
    return results;
}
