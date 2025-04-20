#pragma once

#include "tune.h"
#include "elm_status_bar.hpp"
#include "config/config.hpp"
#include "pm/pm.hpp"

#include <tesla.hpp>

class MainGui final : public tsl::Gui {
  private:
    StatusBar *m_status_bar;

  public:
    MainGui();

    tsl::elm::Element *createUI() final;
    void update() final;
};

class GuiMain : public tsl::Gui {
public:
    virtual tsl::elm::Element* createUI() override {
        auto *rootFrame = new tsl::elm::OverlayFrame("sys-tune", VERSION);
        auto *list = new tsl::elm::List();
        
        auto *whitelistItem = new tsl::elm::ToggleListItem(
            "Whitelist Mode", 
            config::get_whitelist_mode());
        whitelistItem->setStateChangedListener([](bool state) { 
            config::set_whitelist_mode(state); 
        });
        list->addItem(whitelistItem);

        // Add whitelist toggle for current game
        u64 pid{}, tid{};
        pm::getCurrentPidTid(&pid, &tid);
        
        if (tid != 0) {  // Only add the option if we got a valid title ID
            auto *whitelistGameItem = new tsl::elm::ToggleListItem(
                "Whitelist Current Game",
                config::get_title_whitelist(tid));
            whitelistGameItem->setStateChangedListener([tid](bool state) {
                config::set_title_whitelist(tid, state);
            });
            list->addItem(whitelistGameItem);
        }

        rootFrame->setContent(list);
        return rootFrame;
    }
};




