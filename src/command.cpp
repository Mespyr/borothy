#include "command.hpp"

std::string Command::get_description() { return description; };

void Command::run(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    if (requires_cluster)
        command_with_cluster(bot, event);
    else
        command(event);
};

void Command::set_options(dpp::slashcommand& cmd) {
    cmd.set_default_permissions(perms);
    std::for_each(params.begin(), params.end(),
                  [&cmd](dpp::command_option& opt) { cmd.add_option(opt); });
}
