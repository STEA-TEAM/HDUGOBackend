//
// Created by Parti on 2021/1/31.
//

#pragma once

#include <bitset>
#include <json/json.h>
#include <string>
#include <sstream>
#include <trantor/utils/Date.h>

namespace hdugo::utils::misc {
    std::string fromJson(const Json::Value &value, const std::string &indentation = "");

    uint64_t uniform_random(uint64_t size = 99999999);

    std::string fromDate(const uint64_t &milliseconds = 0);

    std::string fromDate(const trantor::Date &date);

    trantor::Date toDate(const std::string &date);

    trantor::Date toDate();

    std::string getFileString(std::string_view path);

    void logger(const std::string &className, const std::string &message);
}
