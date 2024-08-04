#pragma once

#include <dpp/appcommand.h>
#include <dpp/cluster.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>
#include <dpp/message.h>
#include <dpp/permissions.h>
#include <dpp/snowflake.h>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <sstream>
#include <thread>
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
        {"purge",
         Command(purge, "Clear some messages",
                 {dpp::command_option(dpp::co_integer, "limit",
                                      "max amount of messages to delete", true)
                      .set_min_value(1)
                      .set_max_value(100)},
                 dpp::p_administrator)}};
};
