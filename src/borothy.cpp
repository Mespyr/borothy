#include "borothy.hpp"

Borothy::Borothy(const std::string& token) : bot(token) {
    bot.on_log(dpp::utility::cout_logger());
    bot.on_slashcommand(on_command);

    bot.on_ready([this](const dpp::ready_t& event) { this->on_ready(event); });
}

void Borothy::start() { bot.start(dpp::st_wait); }

void Borothy::on_ready(const dpp::ready_t& event) {
    if (dpp::run_once<struct register_bot_commands>()) {
        bot.global_command_create(
            dpp::slashcommand("ping", "Ping pong!", bot.me.id));
    }
}

void Borothy::on_command(const dpp::slashcommand_t& event) {
    if (event.command.get_command_name() == "ping") { event.reply("Pong!"); }
}
