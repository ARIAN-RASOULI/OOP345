// Name: Arian Rasouli
// Email: arasouli4@myseneca.ca
// Student ID: 120393244
// Date: 2025-11-24
//
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my assignments. This submitted piece of work
// has not been shared with any other student or 3rd party content provider.

#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace seneca {

    size_t CustomerOrder::m_widthField = 0;

    
    CustomerOrder::CustomerOrder() {}

    
    CustomerOrder::CustomerOrder(const CustomerOrder& src) {
        throw std::string("ERROR: Cannot make copies.");
    }

    
    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
        *this = std::move(src);
    }

    
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
        if (this != &src) {
            
            if (m_lstItem) {
                for (size_t i = 0; i < m_cntItem; i++)
                    delete m_lstItem[i];
                delete[] m_lstItem;
            }

            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;

            src.m_name.clear();
            src.m_product.clear();
            src.m_lstItem = nullptr;
            src.m_cntItem = 0;
        }
        return *this;
    }

    
    CustomerOrder::CustomerOrder(const std::string& record) {
        Utilities util;
        bool more = true;
        size_t next_pos = 0u;

        m_name = util.extractToken(record, next_pos, more);
        m_product = util.extractToken(record, next_pos, more);

        
        size_t temp_pos = next_pos;
        bool temp_more = more;
        size_t count = 0;

        while (temp_more) {
            util.extractToken(record, temp_pos, temp_more);
            count++;
        }

        m_cntItem = count;
        m_lstItem = new Item * [m_cntItem];

        
        for (size_t i = 0; i < m_cntItem; i++) {
            std::string itemName = util.extractToken(record, next_pos, more);
            m_lstItem[i] = new Item(itemName);
        }

        
        if (m_widthField < util.getFieldWidth()) {
            m_widthField = util.getFieldWidth();
        }
    }

    
    CustomerOrder::~CustomerOrder() {
        if (m_lstItem) {
            for (size_t i = 0; i < m_cntItem; i++)
                delete m_lstItem[i];
            delete[] m_lstItem;
        }
    }

    
    bool CustomerOrder::isOrderFilled() const {
        for (size_t i = 0; i < m_cntItem; i++)
            if (!m_lstItem[i]->m_isFilled)
                return false;
        return true;
    }

    
    bool CustomerOrder::isItemFilled(const std::string& itemName) const {
        for (size_t i = 0; i < m_cntItem; i++) {
            if (m_lstItem[i]->m_itemName == itemName &&
                !m_lstItem[i]->m_isFilled) {
                return false;
            }
        }
        return true;
    }
    
    void CustomerOrder::fillItem(Station& station, std::ostream& os) {
        for (size_t i = 0; i < m_cntItem; i++) {

            if (m_lstItem[i]->m_itemName == station.getItemName() &&
                !m_lstItem[i]->m_isFilled) {

                if (station.getQuantity() > 0) {
                    
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();

                    os << "    Filled " << m_name << ", " << m_product
                        << " [" << m_lstItem[i]->m_itemName << "]\n";
                }
                else {
                    
                    os << "    Unable to fill " << m_name << ", " << m_product
                        << " [" << m_lstItem[i]->m_itemName << "]\n";
                }

                return; 
            }
        }
    }

    
    void CustomerOrder::display(std::ostream& os) const {
        os << m_name << " - " << m_product << "\n";

        for (size_t i = 0; i < m_cntItem; i++) {
            os << "["
                << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber
                << "] ";

            os << std::left << std::setw(m_widthField) << std::setfill(' ')
                << m_lstItem[i]->m_itemName << " - ";

            os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED")
                << "\n";
        }
    }

}
