#include "borothy.hpp"

void ping_pong(const dpp::slashcommand_t& event) {
    dpp::embed   embed = create_one_liner("Pong!");
    dpp::message msg(event.command.channel_id, embed);
    event.reply(msg);
}

void about(const dpp::slashcommand_t& event) {
    dpp::embed embed = dpp::embed()
                           .set_color(dpp::colors::brass)
                           .set_title("Hello!")
                           .set_description(
                               "I'm Borothy, the much cooler version of that "
                               "one character from The Wizard of Oz.");
    dpp::message msg(event.command.channel_id, embed);
    event.reply(msg);
}

void purge(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    dpp::command_value e = event.get_parameter("limit");
    int64_t            limit = std::get<int64_t>(e);
    if (limit < 0) {
        dpp::embed embed =
            create_one_liner("Can't purge a negative number of messages");
        dpp::message msg(event.command.channel_id, embed);
        event.reply(msg);
        return;
    }
    bot.messages_get(
        event.command.channel_id, 0, 0, 0, limit,
        [&bot, event](const dpp::confirmation_callback_t& result) {
            if (result.is_error()) {
                event.reply(result.get_error().human_readable);
                return;
            }
            dpp::message_map message_ids = result.get<dpp::message_map>();
            std::for_each(
                message_ids.begin(), message_ids.end(),
                [&bot, event](std::pair<dpp::snowflake, dpp::message> msg) {
                    bot.message_delete(msg.first, event.command.channel_id);
                });
        });
    // reply
    std::stringstream text;
    text << "Cleared " << limit << " messages!";
    dpp::embed   embed = create_one_liner(text.str());
    dpp::message msg(event.command.channel_id, embed);
    event.reply(msg);
}
