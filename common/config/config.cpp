#include "config/config.hpp"
#include "sdmc/sdmc.hpp"
#include "minIni/minIni.h"
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>

namespace {
    const char CONFIG_PATH[] = "/config/sys-tune/config.ini";
    const char BLACKLIST_PATH[] = "/config/sys-tune/blacklist.ini";
    const char WHITELIST_PATH[] = "/config/sys-tune/whitelist.ini";
    const char PLAYLIST_PATH[] = "/config/sys-tune/playlist.txt";
    
    void create_config_dir() {
        ::sdmc::CreateFolder("/config");
        ::sdmc::CreateFolder("/config/sys-tune");
    }

    auto get_tid_str(u64 tid) -> const char* {
        static char buf[21]{};
        std::sprintf(buf, "%016lX", tid);
        return buf;
    }
}

namespace config {

bool get_autoplay_enabled() {
    return ::ini_getbool("tune", "autoplay_enabled", false, CONFIG_PATH);
}

void set_autoplay_enabled(bool value) {
    create_config_dir();
    ::ini_putl("tune", "autoplay_enabled", value, CONFIG_PATH);
}

bool get_title_blacklist(u64 tid) {
    return ::ini_getbool("blacklist", get_tid_str(tid), false, BLACKLIST_PATH);
}

void set_title_blacklist(u64 tid, bool value) {
    create_config_dir();
    ::ini_putl("blacklist", get_tid_str(tid), value, BLACKLIST_PATH);
}

int get_repeat() {
    return ::ini_getl("tune", "repeat", 0, CONFIG_PATH);
}

void set_repeat(int value) {
    create_config_dir();
    ::ini_putl("tune", "repeat", value, CONFIG_PATH);
}

bool get_shuffle() {
    return ::ini_getbool("tune", "shuffle", false, CONFIG_PATH);
}

void set_shuffle(bool value) {
    create_config_dir();
    ::ini_putl("tune", "shuffle", value, CONFIG_PATH);
}

float get_volume() {
    return static_cast<float>(::ini_getl("tune", "volume", 100, CONFIG_PATH)) / 100.0f;
}

void set_volume(float value) {
    create_config_dir();
    ::ini_putl("tune", "volume", static_cast<long>(value * 100), CONFIG_PATH);
}

float get_default_title_volume() {
    return static_cast<float>(::ini_getl("tune", "default_title_volume", 100, CONFIG_PATH)) / 100.0f;
}

void set_default_title_volume(float value) {
    create_config_dir();
    ::ini_putl("tune", "default_title_volume", static_cast<long>(value * 100), CONFIG_PATH);
}

bool has_title_volume(u64 tid) {
    return ::ini_haskey("volumes", get_tid_str(tid), CONFIG_PATH);
}

float get_title_volume(u64 tid) {
    return static_cast<float>(::ini_getl("volumes", get_tid_str(tid), 100, CONFIG_PATH)) / 100.0f;
}

void set_title_volume(u64 tid, float value) {
    create_config_dir();
    ::ini_putl("volumes", get_tid_str(tid), static_cast<long>(value * 100), CONFIG_PATH);
}

bool has_title_enabled(u64 tid) {
    return ::ini_haskey("enabled", get_tid_str(tid), CONFIG_PATH);
}

bool get_title_enabled(u64 tid) {
    return ::ini_getbool("enabled", get_tid_str(tid), get_title_enabled_default(), CONFIG_PATH);
}

void set_title_enabled(u64 tid, bool value) {
    create_config_dir();
    ::ini_putl("enabled", get_tid_str(tid), value, CONFIG_PATH);
}

bool get_title_enabled_default() {
    return ::ini_getbool("tune", "title_enabled_default", true, CONFIG_PATH);
}

void set_title_enabled_default(bool value) {
    create_config_dir();
    ::ini_putl("tune", "title_enabled_default", value, CONFIG_PATH);
}

std::vector<std::string> get_playlist() {
    std::vector<std::string> playlist;
    long count = ::ini_getl("playlist", "count", 0, CONFIG_PATH);
    
    for (long i = 0; i < count; i++) {
        char key[32];  // Increased buffer size
        snprintf(key, sizeof(key), "track%d", static_cast<int>(i));  // Using %d and casting to int
        char path[1024] = {0};
        if (::ini_gets("playlist", key, "", path, sizeof(path), CONFIG_PATH) > 0) {
            playlist.push_back(path);
        }
    }
    return playlist;
}

void save_playlist(const std::vector<std::string>& playlist) {
    create_config_dir();
    
    ::ini_putl("playlist", "count", playlist.size(), CONFIG_PATH);
    
    for (size_t i = 0; i < playlist.size(); i++) {
        char key[32];  // Increased buffer size
        snprintf(key, sizeof(key), "track%d", static_cast<int>(i));  // Using %d and casting to int
        ::ini_puts("playlist", key, playlist[i].c_str(), CONFIG_PATH);
    }
}

bool get_whitelist_mode() {
    return ::ini_getbool("tune", "whitelist_mode", false, CONFIG_PATH);
}

void set_whitelist_mode(bool value) {
    create_config_dir();
    ::ini_putl("tune", "whitelist_mode", value, CONFIG_PATH);
}

bool get_title_whitelist(u64 tid) {
    if (tid == 0) return false;
    return ::ini_getbool("whitelist", get_tid_str(tid), false, WHITELIST_PATH);
}

void set_title_whitelist(u64 tid, bool value) {
    if (tid == 0) return;
    create_config_dir();
    ::ini_putl("whitelist", get_tid_str(tid), value, WHITELIST_PATH);
}

} // namespace config






