#pragma once

#include <iostream>
#include <map>
#include <typeindex>
#include <any>
#include <optional>
#include <functional>
#include <memory>
#include <list>
#include <set>

#include "sparseArray.hpp"

class Registry {
    public :
        template<typename T>
        using A = typename sparseArray<T>::container_t;
        using entity_t = std::size_t;

        Registry(const std::string &firstScene = "default");

        template<class A>
        sparseArray<A> &register_component();

        template<class A>
        sparseArray<A> &get_components();

        template<class A>
        sparseArray<A> const &get_components() const;

        entity_t spawn_entity();

        void kill_entity(entity_t const &e);

        template<typename Component>
        typename sparseArray<Component>::reference_type add_component(entity_t const &to, Component &&c);

        template<typename Component, typename... Params>
        typename sparseArray<Component>::reference_type emplace_component(entity_t const &to, Params &&... p);

        template<typename Component>
        void remove_component(entity_t const &from);

        template<typename Component>
        bool has_component(entity_t const &entity);

        // template<class... Components, typename Function>
        // void add_system(Function &&f);

        void run_scene_systems();


        struct Scene {
            Scene() = default;
            std::list<std::function<void()>> systems;
            std::set<entity_t> entities;
        };

        const Scene &getScene() const;

        template<class... Components, typename Function>
        void add_system_to_current_scene(Function &&f);

        void add_scene(const std::string &scene, Scene &&sceneObj);

        void add_entity_to_scene(const entity_t &entity, const std::string &scene);
        void add_entity_to_current_scene(const entity_t &entity);

        void change_scene(const std::string &scene);

        void tag_entity(const entity_t &, const std::string &tag);
        void untag_entity(const entity_t &, const std::string &tag);

        const std::set<entity_t> &get_tagged_entities(const std::string &tag);

        /*
        * Check if a system changed the actual scene 
        */
        void handle_scenes();

    private:

        // components containers
        std::unordered_map<std::type_index, std::any> _componentsArrays;
        std::unordered_map<std::type_index, std::function<void(std::any &, std::size_t pos)>> _mapFunctionCreateComponent;
        std::unordered_map<std::type_index, std::function<void(std::any &, std::size_t pos)>> _mapFunctionDeleteComponent;

        // entity ids
        std::size_t entity_number = 0;
        std::set<entity_t> free_ids;
        entity_t entity_from_index(std::size_t idx);
  
        // scenes
        std::unordered_map<std::string, Scene> _scenes;
        std::optional<std::string> _nextScene;
        std::unordered_map<std::string, Scene>::iterator _scene;

        // tags
        std::unordered_map<std::string, std::set<entity_t>> _tags;


};

#include "RegistryImpl.hpp"