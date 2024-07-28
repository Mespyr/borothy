#include "borothy.hpp"

Borothy::Borothy(const std::string& token) : bot(token) {
    bot.on_log(dpp::utility::cout_logger());
    bot.on_slashcommand(on_command);
    bot.on_ready([this](const dpp::ready_t& event) { this->on_ready(event); });
}

void Borothy::start() { bot.start(dpp::st_wait); }

void Borothy::on_ready(const dpp::ready_t& event) {
    if (dpp::run_once<struct register_bot_commands>())
        std::for_each(
            commands.begin(), commands.end(),
            [this](std::pair<std::string, Command> cmd) {
                bot.global_command_create(dpp::slashcommand(
                    cmd.first, cmd.second.get_description(), bot.me.id));
            });
}

void Borothy::on_command(const dpp::slashcommand_t& event) {
    const std::string command_name = event.command.get_command_name();
    if (!commands.count(command_name)) return;
    commands.at(command_name).run(event);
}
