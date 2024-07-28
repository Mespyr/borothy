#include "command.hpp"

const std::string Command::get_description() { return description; };

void Command::run(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    if (requires_cluster)
        command_with_cluster(bot, event);
    else
        command(event);
};
