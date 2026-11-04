#include "Circuit.hpp"
#include "Config.hpp"
#include <cmath>
#include <algorithm>

Circuit::Circuit(const std::string& name, sf::Vector2f pos, const sf::Font& font) : Component(name, pos, font) {
    _pending.active = false;
}

void Circuit::removeComponentAt(sf::Vector2f mousePos) {
    for (int idx = static_cast<int>(_subComponents.size()) - 1; idx >= 0; --idx) {
        if (_subComponents[idx]->getBounds().contains(mousePos)) {
            _subComponents.erase(_subComponents.begin() + idx);
            _connections.erase(
                std::remove_if(_connections.begin(), _connections.end(),
                    [idx](const Connection& c) {
                        return c.fromIdx == static_cast<size_t>(idx) ||
                               c.toIdx   == static_cast<size_t>(idx);
                    }),
                _connections.end());
            for (auto& c : _connections) {
                if (c.fromIdx > static_cast<size_t>(idx)) --c.fromIdx;
                if (c.toIdx   > static_cast<size_t>(idx)) --c.toIdx;
            }
            break;
        }
    }
}

static float pointSegmentDistSq(const sf::Vector2f& p, const sf::Vector2f& a, const sf::Vector2f& b) {
    sf::Vector2f ab = b - a;
    sf::Vector2f ap = p - a;
    float abLenSq = ab.x*ab.x + ab.y*ab.y;
    if (abLenSq == 0.f)
        return ap.x*ap.x + ap.y*ap.y;
    float t = (ap.x*ab.x + ap.y*ab.y) / abLenSq;
    t = std::max(0.f, std::min(1.f, t));
    sf::Vector2f closest = { a.x + ab.x*t, a.y + ab.y*t };
    sf::Vector2f diff = p - closest;
    return diff.x*diff.x + diff.y*diff.y;
}

void Circuit::removeConnectionAt(sf::Vector2f mousePos) {
    const float threshold = LINK_DESTROY_DISTANCE;
    const float thrSq = threshold * threshold;
    for (size_t i = 0; i < _connections.size(); ++i) {
        const Connection& c = _connections[i];
        sf::Vector2f p1 = _subComponents[c.fromIdx]->getPortFullPosition(c.outPort, false);
        sf::Vector2f p2 = _subComponents[c.toIdx]->getPortFullPosition(c.inPort, true);
        if (pointSegmentDistSq(mousePos, p1, p2) < thrSq) {
            _connections.erase(_connections.begin() + i);
            break;
        }
    }
}

void Circuit::addComponent(std::unique_ptr<Component> comp) {
    _subComponents.push_back(std::move(comp));
}

void Circuit::addConnection(size_t f, size_t op, size_t t, size_t ip) {
    _connections.push_back({f, op, t, ip});
}

void Circuit::update() {
    for (auto& comp : _subComponents) {
        comp->update();
    }

    for (const auto& conn : _connections) {
        _subComponents[conn.toIdx]->inputs[conn.inPort].state = _subComponents[conn.fromIdx]->outputs[conn.outPort].state;
    }
}

void Circuit::renderCircuit(sf::RenderWindow& window, sf::Vector2f mousePos) {
    for (const auto& conn : _connections) {
        sf::Vector2f p1 = _subComponents[conn.fromIdx]->getPortFullPosition(conn.outPort, false);
        sf::Vector2f p2 = _subComponents[conn.toIdx]->getPortFullPosition(conn.inPort, true);
        
        sf::Color color = _subComponents[conn.fromIdx]->outputs[conn.outPort].state ? 
                          LINK_ON_COLOR : LINK_OFF_COLOR;
        
        sf::Vertex line[] = { sf::Vertex(p1, color), sf::Vertex(p2, color) };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    if (_pending.active) {
        sf::Vector2f p1 = _subComponents[_pending.fromIdx]->getPortFullPosition(_pending.outPort, false);
        sf::Vertex line[] = { sf::Vertex(p1, LINK_PENDING_COLOR), sf::Vertex(mousePos, LINK_PENDING_COLOR) };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
    for (auto& comp : _subComponents) {
        comp->render(window);
    }
}

void Circuit::handleInteraction(const sf::Vector2f& mousePos) {
    _draggedComponent = nullptr;
    
    for (auto it = _subComponents.rbegin(); it != _subComponents.rend(); ++it) {
        bool clickedPort = false;
        for (auto& p : (*it)->inputs) {
            if (std::hypot(mousePos.x - ((*it)->getPosition().x + p.relativePos.x), 
                           mousePos.y - ((*it)->getPosition().y + p.relativePos.y)) < PIN_USER_INPUT_MARGIN) {
                clickedPort = true;
                break;
            }
        }
        for (auto& p : (*it)->outputs) {
            if (std::hypot(mousePos.x - ((*it)->getPosition().x + p.relativePos.x), 
                           mousePos.y - ((*it)->getPosition().y + p.relativePos.y)) < PIN_USER_INPUT_MARGIN) {
                clickedPort = true;
                break;
            }
        }
        if (clickedPort) return;
        if ((*it)->getBounds().contains(mousePos)) {
            _draggedComponent = it->get();
            _dragOffset = _draggedComponent->getPosition() - mousePos;
            return;
        }
    }
}

void Circuit::handleDrag(sf::Vector2f mousePos) {
    if (_draggedComponent) _draggedComponent->setPosition(mousePos + _dragOffset);
}

void Circuit::endDrag() { _draggedComponent = nullptr; }

void Circuit::startConnection(sf::Vector2f mousePos) {
    for (size_t i = 0; i < _subComponents.size(); ++i) {
        for (size_t p = 0; p < _subComponents[i]->outputs.size(); ++p) {
            sf::Vector2f pPos = _subComponents[i]->getPortFullPosition(p, false);
            if (std::hypot(mousePos.x - pPos.x, mousePos.y - pPos.y) < PIN_USER_INPUT_MARGIN) {
                _pending = { i, p, true };
                return;
            }
        }
    }
}

void Circuit::endConnection(sf::Vector2f mousePos) {
    if (!_pending.active) return;

    for (size_t i = 0; i < _subComponents.size(); ++i) {
        for (size_t p = 0; p < _subComponents[i]->inputs.size(); ++p) {
            sf::Vector2f pPos = _subComponents[i]->getPortFullPosition(p, true);
            if (std::hypot(mousePos.x - pPos.x, mousePos.y - pPos.y) < PIN_USER_INPUT_MARGIN) {
                addConnection(_pending.fromIdx, _pending.outPort, i, p);
                break;
            }
        }
    }
    _pending.active = false;
}