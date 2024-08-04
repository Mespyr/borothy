#include <dpp/message.h>

#include "borothy.hpp"

void ping_pong(const dpp::slashcommand_t& event) {
    dpp::embed embed = create_embed("Pong!");
    event.reply(dpp::message(event.command.channel_id, embed));
}

void about(const dpp::slashcommand_t& event) {
    dpp::embed embed = create_embed("Hello!").set_description(
        "I'm Borothy, the much cooler version of that "
        "one character from The Wizard of Oz.");
    event.reply(dpp::message(event.command.channel_id, embed));
}

void purge(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    // TODO: check permissions for message
    dpp::command_value e = event.get_parameter("limit");
    int64_t            limit = std::get<int64_t>(e);
    bot.messages_get(
        event.command.channel_id, 0, 0, 0, limit,
        [&bot, event, limit](const dpp::confirmation_callback_t& result) {
            if (result.is_error()) {
                dpp::embed embed =
                    create_embed(result.get_error().human_readable);
                event.reply(dpp::message(event.command.channel_id, embed));
                return;
            }
            dpp::message_map msg_map = result.get<dpp::message_map>();
            std::vector<dpp::snowflake> bulk_msg_ids;
            std::vector<dpp::snowflake> individual_msg_ids;

            // calculate time two weeks ago when command was run
            std::chrono::duration time_since_epoch =
                std::chrono::system_clock::now().time_since_epoch();
            uint64_t time_since_epoch_seconds =
                std::chrono::duration_cast<std::chrono::seconds>(
                    time_since_epoch)
                    .count();
            uint64_t two_weeks_ago =
                ((time_since_epoch_seconds - 14 * 24 * 60 * 60) * 1000 -
                 1420070400000)
                << 22;

            for (std::pair<dpp::snowflake, dpp::message> msg_pair : msg_map)
                if (msg_pair.first < two_weeks_ago)
                    individual_msg_ids.push_back(msg_pair.first);
                else
                    bulk_msg_ids.push_back(msg_pair.first);

            // bulk delete raises error if length of bulk_msg_ids is less than 2
            if (bulk_msg_ids.size() >= 2)
                bot.message_delete_bulk(bulk_msg_ids, event.command.channel_id);
            else
                for (dpp::snowflake id : bulk_msg_ids)
                    individual_msg_ids.push_back(id);

            for (dpp::snowflake id : individual_msg_ids) {
                bot.message_delete(id, event.command.channel_id);
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
            dpp::embed embed = create_embed(
                "Finished clearing " + std::to_string(limit) + " messages!");
            event.edit_original_response(
                dpp::message(event.command.channel_id, embed)
                    .set_flags(dpp::m_ephemeral));
        });
	event.thinking(true);
}
