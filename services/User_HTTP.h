//
// Created by Parti on 2021/2/4.
//

#pragma once

#include <bitset>
#include <HdugoCore/HdugoCore.h>
#include <plugins/Configurator.h>
#include <utils/http.h>

namespace hdugo::services::http {
    class User {
    public:
        User() = default;

        Json::Value loginAccount(
                drogon::HttpStatusCode &code,
                const Json::Value &request
        );

        Json::Value getUserBrief(
                drogon::HttpStatusCode &code,
                const Json::Value &request
        );

    private:
        hdugo::core::HdugoCore _hdugoCore{};
    };
}
