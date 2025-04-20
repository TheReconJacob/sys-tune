#pragma once
#include <switch.h>
#include <string>
#include <vector>

namespace config {

bool get_autoplay_enabled();
void set_autoplay_enabled(bool value);

bool get_title_blacklist(u64 tid);
void set_title_blacklist(u64 tid, bool value);

int get_repeat();
void set_repeat(int value);

bool get_shuffle();
void set_shuffle(bool value);

float get_volume();
void set_volume(float value);

float get_default_title_volume();
void set_default_title_volume(float value);

bool has_title_volume(u64 tid);
float get_title_volume(u64 tid);
void set_title_volume(u64 tid, float value);

bool has_title_enabled(u64 tid);
bool get_title_enabled(u64 tid);
void set_title_enabled(u64 tid, bool value);

bool get_title_enabled_default();
void set_title_enabled_default(bool value);

// New playlist functions
std::vector<std::string> get_playlist();
void save_playlist(const std::vector<std::string>& playlist);

} // namespace config


