// Name: Arian Rasouli
// Email: arasouli4@myseneca.ca
// Student ID: 120393244
// Date: 2025-11-22
//
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my assignments. This submitted piece of work
// has not been shared with any other student or 3rd party content provider.


#include "Station.h"
#include "Utilities.h"
#include <iomanip>

namespace seneca {

    size_t Station::m_widthField = 0;
    int Station::id_generator = 0;

    Station::Station(const std::string& record) {
        Utilities util;
        bool more = true;
        size_t next_pos = 0u;

        m_id = ++id_generator;

        m_itemName = util.extractToken(record, next_pos, more);

        std::string token = util.extractToken(record, next_pos, more);
        m_serialNumber = static_cast<size_t>(std::stoul(token));

        token = util.extractToken(record, next_pos, more);
        m_quantity = static_cast<size_t>(std::stoul(token));

        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }

        if (more) {
            m_description = util.extractToken(record, next_pos, more);
        }
        else {
            m_description.clear();
        }
    }

    const std::string& Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_serialNumber++;
    }

    size_t Station::getQuantity() const {
        return m_quantity;
    }

    void Station::updateQuantity() {
        if (m_quantity > 0) {
            --m_quantity;
        }
    }

    void Station::display(std::ostream& os, bool full) const {
        os << std::setw(3) << std::setfill('0') << m_id << " | ";
        os << std::left << std::setw(m_widthField) << std::setfill(' ') << m_itemName << " | ";
        os << std::right << std::setw(6) << std::setfill('0') << m_serialNumber << " | ";

        if (full) {
            os << std::setw(4) << std::setfill(' ') << m_quantity << " | ";
            os << m_description;
        }

        os << '\n';
        os << std::setfill(' ');
    }

}
