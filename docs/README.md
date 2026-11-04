Welcome to the NanoTekSpice documentation.
If you are here, it's because you are interested in how the project works internally or because you want to add new components.

## **1. Architecture of project**

NanoTekSpice works in several steps.
First, the .nts file is parsed to extract the components and the links between them.
Then the components are created using the factory.
Finally, the simulation loop calls compute() on the components to evaluate the circuit.

## **2. IComponent Interface**

To add a new component, your class must inherit from the `IComponent` interface.
The interface is located in `include/IComponent.hpp`.

It is composed of three functions that are explained in the abstract class section.

WARNING: You must not modify this interface.

## **3. Abstract Class `AComponent`**

AComponent is an abstract class implementing part of IComponent.
The abstract is located in `include/AComponent.hpp` and `include/AComponent.cpp`.

It stores the links between components and provides helper methods used by most components.

`AComponent` is an abstract class that implements part of the `IComponent` interface.
Its goal is to provide common functionality for most components, so that new components only need to implement their own logic.
Most components in NanoTekSpice inherit from this class instead of directly inheriting from `IComponent`.

---
**__Links Between Components__**
Each component can be connected to other components using pins.

The `Link` class represents a connection between two components.

class Link {
public:
    Link(std::size_t pin, nts::IComponent *component);
};

Each link stores:
- the pin number of the connected component
- a pointer to the linked component

`AComponent` stores all links in the following structure:

std::unordered_map<std::size_t, std::vector<Link>> _links;

This map associates a pin number with all the components connected to it.

**__Main Functions__**

__setLink__

void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);

This function connects two components together.

It stores the link between:
- pin of the current component
- otherPin of the other component

__getLink__
nts::Tristate getLink(std::size_t pin);

This function retrieves the value of a connected pin by calling `compute()` on the linked component.
If multiple outputs are connected to the same pin, their values must be consistent.

__compute__
virtual nts::Tristate compute(std::size_t pin) = 0;

This function must be implemented by every component.
It returns the logical value of a given pin.

Possible values are:
- True
- False
- Undefined

__Computation Cache__

To avoid computing the same value multiple times during a simulation tick, `AComponent` implements a caching system.
It uses the global variable:

extern std::size_t gEvalId;

Each time a simulation step is executed, this value changes.
The component stores:
- the last evaluation id
- the last computed value

std::vector<std::size_t> _lastEvalIds;
std::vector<nts::Tristate> _lastReturnValues;

Helper functions are provided:

shouldCompute(pin)
cachedValue(pin)
storeValue(pin, value)

This prevents infinite recursion and unnecessary recomputations.

__Constructor__

AComponent(std::string name, std::size_t nb_links);

The constructor initializes:
- the component name
- the number of pins
- the link storage

Each pin is prepared to store connections.

## **4. Factory**

The Factory class is responsible for creating components dynamically from the type defined in the .nts file.
When the parser reads the .chipsets section, it encounters lines like:

```bash
input a
and gate
output out
```

The first value represents the component type, and the second value represents the component name.
The factory uses the type to create the correct component.

**Component Creation**

The factory contains a map that associates a component type with a function used to create the component.

Example:

std::unordered_map<std::string, std::function<std::unique_ptr<IComponent>(const std::string&)>> _factory;

Each entry in this map contains:
- the name of the component type
- a function that constructs the component

Example:

_factory["and"] = [](const std::string &name) {
    return std::make_unique<AndComponent>(name);
};

When the parser encounters a component type, the factory searches for it in this map.

**createComponent**

std::unique_ptr<IComponent> createComponent(const std::string &type, const std::string &name);

This function creates a component based on its type.

Steps:
1. Search the type in the factory map.
2. If the type exists, call the associated constructor.
3. If the type does not exist, throw an exception.

Example:

auto component = factory.createComponent("and", "gate1");

**Component Storage**

The factory also stores all created components:

std::unordered_map<std::string, std::unique_ptr<IComponent>> _components;

This map associates:
- the component name
- the component instance

Example:

_components["gate"] = factory.createComponent("and", "gate");

**getComponent**

nts::IComponent& getComponent(const std::string& name);

This function retrieves a component using its name.

If the component does not exist, an exception is thrown.

Example:
nts::IComponent &gate = factory.getComponent("gate");


**Why Use a Factory**

The factory pattern allows the program to:

- create components dynamically
- avoid large if or switch statements
- easily add new components

To add a new component, you only need to register it in the factory.


## **5. How to Add a New Component**

Adding a new component in NanoTekSpice is simple thanks to the project architecture.
Most components inherit from the abstract class `AComponent`, which already provides
common logic such as link management and caching.

__Step 1 — Create a New Class__

Create a new class for your component and make it inherit from `AComponent`.

Example:

class MyGate : public nts::AComponent {
public:
    MyGate(const std::string &name) : AComponent(name, 3) {}

    nts::Tristate compute(std::size_t pin) override;
};

The second parameter of the constructor corresponds to the number of pins.
Don't forget the includes.


__Step 2 — Implement compute()__

Each component must implement the `compute()` function.
This function returns the logical value of the requested pin.

Example:

```bash
nts::Tristate MyGate::compute(std::size_t pin)
{
    if (!shouldCompute(pin))
        return cachedValue(pin);

    nts::Tristate a = getLink(1);
    nts::Tristate b = getLink(2);

    nts::Tristate result = (a == nts::True && b == nts::True) ? nts::True : nts::False;

    storeValue(pin, result);
    return result;
}
```

__Step 3 — Register the Component in the Factory__

To make the component usable from a `.nts` file, it must be registered in the factory.

Example:

```bash
_factory["mygate"] = [](const std::string &name) { return std::make_unique<MyGate>(name); };
```

You can see the examples at
```src/Factory/Factory.cpp```
After this step, the component can be used in a circuit description file.

Example `.nts`:

.chipsets:
mygate gate1


__Step 4 — Connect Pins__

Pins are connected using the `.links` section of the `.nts` file.

Example:

.links:
a:1 gate1:1
b:1 gate1:2
gate1:3 out:1


__Summary__

To add a new component you must:

1. Create a new class inheriting from `AComponent`
2. Implement the `compute()` function
3. Register the component in the factory

After these steps, the component can be used directly in `.nts` circuit files.

**May the force be with you**