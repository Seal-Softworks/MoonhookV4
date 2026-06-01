#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace moon {

class Webhook {
public:
    struct Embed {
        std::string title;
        std::string description;
        int color = 0x000000;
        std::string footer;
        std::string thumbnail;
        std::string image;
        
        struct Field {
            std::string name;
            std::string value;
            bool is_inline = false;
        };
        std::vector<Field> fields;

        nlohmann::json to_json() const;
    };

    explicit Webhook(const std::string& url);

    bool send(const std::string& content);
    bool send(const Embed& embed);
    bool send(const std::string& content, const std::vector<Embed>& embeds);

    void set_proxy(const std::string& proxy);
    const std::string& get_proxy() const;
    const std::string& last_error() const;
    int retry_after_ms() const;

    bool set_name(const std::string& name);

private:
    std::string m_url;
    std::string m_proxy;
    std::string m_last_error;
    int m_retry_after_ms = 0;
};

} // namespace moon