// Name: Arian Rasouli
// Email: arasouli4@myseneca.ca
// Student ID: 120393244
// Date: 2025-11-22
//
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my assignments. This submitted piece of work
// has not been shared with any other student or 3rd party content provider.


#include "Utilities.h"
#include <stdexcept>
#include <iomanip>

namespace seneca {

    char Utilities::m_delimiter = ' ';

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    static std::string trim(const std::string& src) {
        size_t begin = src.find_first_not_of(' ');
        if (begin == std::string::npos) return {};
        size_t end = src.find_last_not_of(' ');
        return src.substr(begin, end - begin + 1);
    }

    std::string Utilities::extractToken(const std::string& str,
        size_t& next_pos,
        bool& more) {
        if (next_pos > str.length()) {
            more = false;
            return {};
        }

        size_t delimPos = str.find(m_delimiter, next_pos);

        if (delimPos == next_pos) {
            more = false;
            throw std::string("No token.");
        }

        std::string token;

        if (delimPos == std::string::npos) {
            token = str.substr(next_pos);
            next_pos = str.length() + 1;
            more = false;
        }
        else {
            token = str.substr(next_pos, delimPos - next_pos);
            next_pos = delimPos + 1;
            more = true;
        }

        token = trim(token);

        if (token.empty()) {
            more = false;
            throw std::string("No token.");
        }

        if (m_widthField < token.length()) {
            m_widthField = token.length();
        }

        return token;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }

}
