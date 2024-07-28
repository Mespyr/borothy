#pragma once

#include <dpp/appcommand.h>
#include <dpp/cluster.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/message.h>
#include <dpp/snowflake.h>
#include <dpp/appcommand.h>

#include <algorithm>
#include <cstdint>
#include <sstream>
#include <unordered_map>

#include "../command.hpp"
#include "../util.hpp"

// commands
void ping_pong(const dpp::slashcommand_t& event);
void about(const dpp::slashcommand_t& event);
void purge(dpp::cluster& bot, const dpp::slashcommand_t& event);

class Borothy {
  public:
    Borothy(const std::string& token);
    void start();

  private:
    dpp::cluster bot;

    void on_ready(const dpp::ready_t& event);
    void on_command(const dpp::slashcommand_t& event);

    // command map
    static inline std::unordered_map<std::string, Command> commands = {
        {"ping", Command(ping_pong, "Ping pong!")},
        {"about", Command(about, "Learn about Borothy")},
        {"purge", Command(purge, "Delete some messages")}};
};
