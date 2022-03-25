//
// Created by Parti on 2021/2/4.
//

#include <drogon/HttpClient.h>
#include <services/User_HTTP.h>
#include <utils/HtmlParser.h>
#include <utils/misc.h>

using namespace drogon;
using namespace hdugo::core;
using namespace hdugo::plugins;
using namespace hdugo::services::http;
using namespace hdugo::utils;
using namespace std;

Json::Value User::loginAccount(
        HttpStatusCode &code,
        const Json::Value &request
) {
    Json::Value response;
    if (!(request.isMember("username") && request["username"].isString() &&
          request.isMember("password") && request["password"].isString())) {
        code = k400BadRequest;
        response["type"] = "Error";
        response["reason"] = "Wrong format: Requires string type 'username' and 'password'";
        return response;
    }
    code = k200OK;
    response = _hdugoCore.loginAccount(
            request["username"].asString(),
            request["password"].asString()
    );
    return response;
}

Json::Value User::getUserBrief(
        HttpStatusCode &code,
        const Json::Value &request
) {
    Json::Value response;
    if (!(request.isMember("JSESSIONID") && request["JSESSIONID"].isString() &&
          request.isMember("route") && request["route"].isString())) {
        code = k400BadRequest;
        response["type"] = "Error";
        response["reason"] = "Wrong format: Requires string type 'JSESSIONID' and 'route'";
        return response;
    }
    auto result = _hdugoCore.getUserBrief(
            request["JSESSIONID"].asString(),
            request["route"].asString()
    );
    HtmlParser htmlParser(result["data"]["responseBody"].asString());
    code = k200OK;
    response["type"] = "Success";
    response["data"]["info"] = htmlParser.getElements(
            "media-body",
            HtmlParser::Selector::className
    )[0];
    response["data"]["DOM"] = htmlParser.toJson();
    return response;
}
