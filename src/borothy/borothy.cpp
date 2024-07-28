#include "borothy.hpp"

Borothy::Borothy(const std::string& token) : bot(token) {
    bot.on_log(dpp::utility::cout_logger());
    bot.on_slashcommand(
        [this](const dpp::slashcommand_t& event) { this->on_command(event); });
    bot.on_ready([this](const dpp::ready_t& event) { this->on_ready(event); });
}

void Borothy::start() { bot.start(dpp::st_wait); }

void Borothy::on_ready(const dpp::ready_t& event) {
    // uncomment when adding new commands or changing names of old ones
    // bot.global_bulk_command_delete();
    if (dpp::run_once<struct register_bot_commands>())
        std::for_each(
            commands.begin(), commands.end(),
            [this](std::pair<std::string, Command> cmd) {
                dpp::slashcommand m =
                    dpp::slashcommand(cmd.first, cmd.second.get_description(),
                                      bot.me.id)
                        .add_option(dpp::command_option(
                            dpp::co_integer, "limit",
                            "max amount of messages to delete", true));
                bot.global_command_create(m);
            });
}

void Borothy::on_command(const dpp::slashcommand_t& event) {
    const std::string command_name = event.command.get_command_name();
    if (!commands.count(command_name)) return;
    commands.at(command_name).run(bot, event);
}
