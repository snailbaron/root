#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <deque>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <optional>
#include <type_traits>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

class Entity {
public:
    using ValueType = uint64_t;

    explicit Entity(ValueType id) : _id(id) {}

    ValueType operator*() const
    {
        return _id;
    }

    operator ValueType() const
    {
        return **this;
    }

    friend bool operator==(Entity lhs, Entity rhs)
    {
        return lhs._id == rhs._id;
    }

    friend bool operator!=(Entity lhs, Entity rhs)
    {
        return lhs._id != rhs._id;
    }

    friend bool operator<(Entity lhs, Entity rhs)
    {
        return lhs._id < rhs._id;
    }

    friend bool operator>(Entity lhs, Entity rhs)
    {
        return lhs._id > rhs._id;
    }

    friend bool operator<=(Entity lhs, Entity rhs)
    {
        return lhs._id <= rhs._id;
    }

    friend bool operator>=(Entity lhs, Entity rhs)
    {
        return lhs._id >= rhs._id;
    }

private:
    ValueType _id;
};

namespace std {

template <> struct hash<Entity> {
    std::size_t operator()(const Entity& entity) const noexcept
    {
        return std::hash<Entity::ValueType>{}(*entity);
    }
};

} // namespace std

class EntityPool {
public:
    Entity createEntity();
    void killEntity(Entity entity);

private:
    std::deque<Entity> _freeEntities;
    Entity::ValueType _nextEntity = 0;
};

class BaseComponentManager {
public:
    virtual ~BaseComponentManager() {}
    virtual void killEntity(Entity entity) = 0;
};

template <class ComponentType>
class ComponentManager : public BaseComponentManager {
    static_assert(std::is_default_constructible<ComponentType>());

public:
    const ComponentType* component(Entity entity) const
    {
        if (auto it = _indexByEntity.find(entity); it != _indexByEntity.end()) {
            return &_components.at(it->second);
        } else {
            return nullptr;
        }
    }

    ComponentType* component(Entity entity)
    {
        if (auto it = _indexByEntity.find(entity); it != _indexByEntity.end()) {
            return &_components.at(it->second);
        } else {
            return nullptr;
        }
    }

    const auto& components() const
    {
        return _components;
    }

    auto& components()
    {
        return _components;
    }

    const auto& entities() const
    {
        return _entities;
    }

    ComponentType& add(Entity entity)
    {
        _indexByEntity[entity] = _entities.size();
        _entities.push_back(entity);
        return _components.emplace_back();
    }

    void killEntity(Entity entity) override
    {
        auto mapIterator = _indexByEntity.find(entity);
        if (mapIterator == _indexByEntity.end()) {
            return;
        }

        size_t index = mapIterator->second;
        _indexByEntity.erase(mapIterator);
        if (index + 1 < _entities.size()) {
            _indexByEntity[_entities.back()] = index;
            std::swap(_entities.at(index), _entities.back());
            std::swap(_components.at(index), _components.back());
        }
        _entities.pop_back();
        _components.pop_back();
    }

private:
    std::vector<Entity> _entities;
    std::vector<ComponentType> _components;
    std::unordered_map<Entity, size_t> _indexByEntity;
};

class EntityManager {
public:
    template <class ComponentType>
    ComponentType* component(Entity entity)
    {
        return componentManager<ComponentType>().component(entity);
    }

    template <class ComponentType>
    auto& components()
    {
        return componentManager<ComponentType>().components();
    }

    template <class ComponentType>
    auto& entities()
    {
        return componentManager<ComponentType>().entities();
    }

    template <class ComponentType>
    ComponentType& add(Entity entity)
    {
        return componentManager<ComponentType>().add(entity);
    }

    Entity createEntity()
    {
        return _entityPool.createEntity();
    }

    void killEntity(Entity entity)
    {
        _entityPool.killEntity(entity);
        for (auto& [typeIndex, componentManager] : _componentManagers) {
            componentManager->killEntity(entity);
        }
    }

private:
    template <class ComponentType>
    ComponentManager<ComponentType>& componentManager()
    {
        auto foundIt = _componentManagers.find(typeid(ComponentType));
        if (foundIt == _componentManagers.end()) {
            auto [insertedIt, success] = _componentManagers.insert({
                typeid(ComponentType),
                std::make_unique<ComponentManager<ComponentType>>()});
            foundIt = insertedIt;
        }
        return static_cast<ComponentManager<ComponentType>&>(*foundIt->second);
    }

    EntityPool _entityPool;
    std::unordered_map<
        std::type_index,
        std::unique_ptr<BaseComponentManager>> _componentManagers;
};
