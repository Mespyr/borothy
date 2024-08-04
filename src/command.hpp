#pragma once

#include <dpp/appcommand.h>
#include <dpp/cluster.h>
#include <dpp/dispatcher.h>
#include <dpp/permissions.h>

#include <functional>
#include <vector>

class Command {
  public:
    Command(
        std::function<void(dpp::cluster&, const dpp::slashcommand_t&)> command,
        const std::string&               description,
        std::vector<dpp::command_option> params = {},
        dpp::permission                  perms = dpp::p_send_messages)
        : command_with_cluster(command),
          description(description),
          params(params),
          perms(perms),
          requires_cluster(true) {}

    Command(std::function<void(const dpp::slashcommand_t&)> command,
            const std::string&                              description,
            std::vector<dpp::command_option>                params = {},
            dpp::permission perms = dpp::p_send_messages)
        : command(command),
          description(description),
          params(params),
          perms(perms),
          requires_cluster(false) {}

    std::string get_description();

    void run(dpp::cluster& bot, const dpp::slashcommand_t& event);
    void set_options(dpp::slashcommand& cmd);

  private:
    std::function<void(dpp::cluster&, const dpp::slashcommand_t&)>
                                                    command_with_cluster;
    std::function<void(const dpp::slashcommand_t&)> command;

    std::string                      description;
    std::vector<dpp::command_option> params;
    dpp::permission                  perms;
    bool                             requires_cluster;
};
