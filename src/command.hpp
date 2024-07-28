#pragma once

#include <dpp/dispatcher.h>

class Command {
  public:
    Command(const std::string& desc,
            void (*command_func)(const dpp::slashcommand_t&))
        : description(desc), command(command_func) {}

    const std::string get_description() { return description; };

    void run(const dpp::slashcommand_t& event) { command(event); };

  private:
    const std::string description;
    void (*command)(const dpp::slashcommand_t&);
};
