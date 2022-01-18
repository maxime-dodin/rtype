<h1>Rtype documentation</h1>

<h2>ECS</h2>
A manager of our components added in our game<br/>
List of components : <br/>
- Animations ...
- Controllable ...
- IU ...
- Position ...
- Sprite ...
- Velocity ...

The registry is a manager of all our list of components (in sparse_array class)<br/>
List of methods in Registery.hpp<br/>
Methods:
- ```Registery()``` : constructor of registery create a default scene named "default"
- ```Registery("scene1")``` : constructor create a scene as the name of your string, here "scene1"
- ```sparseArray<A> &register_component()``` : add a component of Type A in our registery
- ```sparseArray<A> &get_components()```: get all components of type A, in your system_fonctions you can iterate on it (see under)
- ```sparseArray<A> const &get_components() const``` : same as get_comonent but a const reference is returned
- ```entity_t spawn_entity()```: spawn_an entity on your register, you can add components to it after (see under). It returns you the id of the entity
- ```void kill_entity(entity_t const &e)```: destroy the entity by his id
- ```reference_type add_component(entity_t const &to, Component &&c)```: add a "c" component to "to" the entity at the end of 
- ```reference_type emplace_component(entity_t const &to, Params &&... p)```: emplace a "p" component(s) to "to" the entity. You can add however you want components
- ```template<typename Component> void remove_component(entity_t const &from)```: remove the Component "Component" in template parameter of the entity (by entity id)
- ```template<typename Component> bool has_component(entity_t const &entity)```: check if the component of an entity exist or not (true if it does, ether false)
- ```template<class... Components, typename Function> void add_system_to_current_scene(Function &&f)```: add a system (f) to your list of systems at the end of the std::vector<std::function()> systems
- ```void run_scene_systems()```: run all the systems add to you list of systems (std::vector<std::function()> systems) by sorting of added (first added, first played)
- ```
  struct Scene {
            Scene() = default;
            std::list<std::function<void()>> systems;
            std::list<entity_t> entities;
        };
  ```
  The scenes as a string and contains a list of systems (for the logic of the scene), and entities to display them
- ```void add_scene(const std::string &scene, Scene &&sceneObj);```: create a scene by string and add your objects to them by the scene Struct (just over here)
- ```void add_entity_to_scene(const entity_t &entity, const std::string &scene)```: add an entity to display on your scene by id (the entity must be created before)
- ```void add_entity_to_current_scene(const entity_t &entity)```: the current scene is the one you currently are (named in your constructor or in change_scene("sceneName"))
- ```void change_scene(const std::string &scene)```: changing scene by name (you must have created the scene before)
- ```void tag_entity(const entity_t &, const std::string &tag)```: put a tag on your entity (tags can be used to display entities named by a tag before or after, or to collide entities with a specific tag). You can add multiple tag on an entity.
- ```void untag_entity(const entity_t &, const std::string &tag)```: remove the tag of the entity by id and name of the tag
- ```const std::vector<entity_t> &get_tagged_entities(const std::string &tag)```: get a list (std::vector<entity_t>) of all entities named by a tag
<p style = "font-size:20px;">...Variables ?<p>
<h2>Netword and protocol</h2>


#UDP protocole

size_t typeHeader<br/>
size_t lenBody<br/>
size_t *body (-> last data is always the entity idx in ecs registery)<br/>
<br/>
- typeHeader 0 -> MovePositions<br/>
- typeHeader 1 -> Spawn/Kill entity<br/>
- typeHeader 2 -> GameEvent<br/>
<br/>
Message from type MovePosition - Body :<br/>
{"\t"}[0] = posX, [1] = posY, [2] = entity idx
<br/>
Message from type GameEvent - Body :<br/>
{"\t"}[0] = typeOfInput : 1 -> move player
{"\t\t"}[1] = 0 -> no moves in X / [1] = 1 -> right move / [1] -> left move
{"\t\t"}[2] = 0 -> no moves in X / [1] = 1 -> down move / [1] -> up move
{"\t\t"}[3] enity idx
{"\t"}[0] = typeOfInput : 2 -> idk yet
...