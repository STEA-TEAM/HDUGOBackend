//
// Created by Parti on 2021/2/3.
//

#pragma once

#include <drogon/HttpController.h>
#include <services/User_HTTP.h>

namespace hdugo::api::v1 {
    class User : public drogon::HttpController<User> {
    public:
        METHOD_LIST_BEGIN
            METHOD_ADD(User::loginAccount, "/login", drogon::Post);
            METHOD_ADD(User::getUserInfo, "/info", drogon::Post);
        METHOD_LIST_END

        void loginAccount(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

        void getUserInfo(const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    private:
        services::http::User _service;
    };
}
