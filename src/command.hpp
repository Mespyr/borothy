#pragma once

#include <dpp/cluster.h>
#include <dpp/dispatcher.h>

class Command {
  public:
    Command(
        std::function<void(dpp::cluster&, const dpp::slashcommand_t&)> command,
        const std::string& description)
        : command_with_cluster(command),
          description(description),
          requires_cluster(true) {}

    Command(std::function<void(const dpp::slashcommand_t&)> command,
            const std::string&                              description)
        : command(command), description(description), requires_cluster(false) {}

    const std::string get_description();

    void run(dpp::cluster& bot, const dpp::slashcommand_t& event);

  private:
    std::function<void(dpp::cluster&, const dpp::slashcommand_t&)>
                                                    command_with_cluster;
    std::function<void(const dpp::slashcommand_t&)> command;

    const std::string description;
    bool              requires_cluster;
};
