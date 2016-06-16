#pragma once

#include <string>
#include <vector>

namespace pl {


template <typename T>
class CommandLineArgument
{
public:
    CommandLineArgument(std::string &name,
                        std::string &description = std::string())
        :
            mName(name),
            mDescription(description)
    {

    }

    CommandLineArgument(std::string &name,
                        T defaultValue,
                        std::string &description = std::string())
        :
            mName(name),
            mDescription(description),
            mDefaultValue(defaultValue)
    {

    }

    CommandLineArgument(std::string &name,
                        std::vector<T> &allowedValues,
                        std::string &description = std::string())
        :
            mName(name),
            mDescription(description),
            mAllowedValues(allowedValues)
    {

    }

    CommandLineArgument(std::string &name,
                        T &defaultValue,
                        std::vector<T> &allowedValues,
                        std::string &description = std::string())
        :
            mName(name),
            mDescription(description),
            mDefaultValue(defaultValue),
            mAllowedValues(allowedValues)
    {

    }

    CommandLineArgument& withDefaultValue(T &&value) {
        this->mDefaultValue = value;
        return *this;
    }

    CommandLineArgument& withAllowedValues(std::vector<T> &&values) {
        this->mAllowedValues = values;
        return *this;
    }

    std::string name() const {
        return this->mName;
    }

    std::string description() const {
        return this->mDescription;
    }

    bool optional() const {
        return this->mOptional;
    }

    T value() const {
        return this->mValue;
    }

    T defaultValue() const {
        return this->mDefaultValue;
    }

    std::vector<T> allowedValues() const {
        return this->mAllowedValues;
    }

private:
    std::string mName;
    std::string mDescription;

    T mValue;
    T mDefaultValue;
    std::vector<T> mAllowedValues;
    bool mOptional;
};


}
