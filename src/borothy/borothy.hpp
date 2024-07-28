#pragma once

#include <dpp/appcommand.h>
#include <dpp/dispatcher.h>
#include <dpp/dpp.h>

#include <algorithm>
#include <unordered_map>

#include "../command.hpp"

class Borothy {
  public:
    Borothy(const std::string& token);
    void start();

  private:
    dpp::cluster bot;

    void        on_ready(const dpp::ready_t& event);
    static void on_command(const dpp::slashcommand_t& event);

    // commands
    static void ping_pong(const dpp::slashcommand_t& event);
    static void about(const dpp::slashcommand_t& event);
    static void purge(const dpp::slashcommand_t& event);

    static inline std::unordered_map<std::string, Command> commands = {
        {"ping", Command("Ping pong!", ping_pong)},
        {"about", Command("Learn about Borothy", about)},
        {"purge", Command("Delete some messages", purge)}};
};
