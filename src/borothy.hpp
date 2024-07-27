#pragma once

#include <dpp/dpp.h>

class Borothy {
  public:
    Borothy(const std::string& token);
    void start();

  private:
    dpp::cluster bot;

    void        on_ready(const dpp::ready_t& event);
    static void on_command(const dpp::slashcommand_t& event);
};
