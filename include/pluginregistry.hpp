#pragma once
#include <vector>
#include <option.hpp>

class Registry {
public:
    static Registry& Get() {
        static Registry instance;
        return instance;
    }

    void AddOption(Option opt) {
        options.push_back(std::move(opt));
    }

    std::vector<Option>& GetOptions() { return options; }

    void ClearOptions() { options.clear(); }

private:
    Registry() = default;
    std::vector<Option> options;
};