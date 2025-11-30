// Name: Arian Rasouli
// Email: arasouli4@myseneca.ca
// Student ID: 120393244
// Date: 2025-11-29
//
// I declare that this submission is the result of my own work and I only copied the code
// that my professor provided to complete my assignments. This submitted piece of work
// has not been shared with any other student or 3rd party content provider.
#include <fstream>
#include <algorithm>
#include "LineManager.h"
#include "Utilities.h"

namespace seneca {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations) {
        std::ifstream fin(file);
        if (!fin)
            throw std::string("Unable to open [") + file + "] file";

        Utilities util;
        std::string line;
        bool more{ true };

        while (std::getline(fin, line)) {
            size_t pos = 0;
            more = true;

            std::string src = util.extractToken(line, pos, more);
            std::string dst = more ? util.extractToken(line, pos, more) : "";

            Workstation* pSrc = nullptr;
            Workstation* pDst = nullptr;

            auto itSrc = std::find_if(stations.begin(), stations.end(),
                [&](Workstation* ws) { return ws->getItemName() == src; });
            if (itSrc != stations.end())
                pSrc = *itSrc;

            if (!dst.empty()) {
                auto itDst = std::find_if(stations.begin(), stations.end(),
                    [&](Workstation* ws) { return ws->getItemName() == dst; });
                if (itDst != stations.end())
                    pDst = *itDst;
            }

            if (pSrc)
                pSrc->setNextStation(pDst);

            m_activeLine.push_back(pSrc);
        }

        m_firstStation = nullptr;
        for (auto* ws : m_activeLine) {
            bool found = false;
            for (auto* other : m_activeLine) {
                if (other && other->getNextStation() == ws) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                m_firstStation = ws;
                break;
            }
        }

        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations() {
        std::vector<Workstation*> ordered;
        Workstation* current = m_firstStation;
        while (current) {
            ordered.push_back(current);
            current = current->getNextStation();
        }
        m_activeLine = ordered;
    }

    bool LineManager::run(std::ostream& os) {
        static size_t iteration = 0;
        os << "Line Manager Iteration: " << ++iteration << "\n";

        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto* ws : m_activeLine)
            ws->fill(os);

        for (auto* ws : m_activeLine)
            ws->attemptToMoveOrder();

        return g_completed.size() + g_incomplete.size() == m_cntCustomerOrder;
    }



    void LineManager::display(std::ostream& os) const {
        for (auto* ws : m_activeLine)
            ws->display(os);
    }

}
