#include "util.hpp"

dpp::embed create_one_liner(std::string msg) {
    return dpp::embed().set_color(dpp::colors::brass).set_title(msg);
}
