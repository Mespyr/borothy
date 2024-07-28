#include <dpp/colors.h>
#include "borothy.hpp"

void Borothy::ping_pong(const dpp::slashcommand_t& event) {
    event.reply("Pong!");
}

void Borothy::about(const dpp::slashcommand_t& event) {
	dpp::embed about_embed = dpp::embed()
		.set_color(dpp::colors::aztech_purple)
		.set_title("Hello!")
		.set_description("I'm Borothy, the much cooler version of the main character of The Wizard of Oz.");
    dpp::message msg(event.command.channel_id, about_embed);
    event.reply(msg);
}


void Borothy::purge(const dpp::slashcommand_t& event) {
    event.reply("Not done yet!");
}
