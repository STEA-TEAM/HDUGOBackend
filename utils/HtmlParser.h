//
// Created by Particle_G on 2021/8/6.
//

#pragma once

#include <functional>
#include <json/json.h>
#include <string>
#include <libxml/HTMLparser.h>

namespace hdugo::utils {
    class HtmlParser {
    public:
        enum class Selector {
            className,
            id,
            elementName,
            attributeName,
        };

        explicit HtmlParser(const std::string &rawHtml);

        [[nodiscard]] Json::Value toJson() const;

        Json::Value getElements(
                const std::string &query,
                const Selector &selector
        );

    private:
        Json::Value _docJson;

        void _traverse(
                xmlNode *currentNode,
                Json::Value &json
        ) const;

        void _select(
                const Json::Value &input,
                Json::Value &output,
                const Selector &selector,
                const std::function<bool(const std::string&)> &filter
        ) const;
    };

}



