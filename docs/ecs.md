# RType Entity-Component-System (ECS) Documentation

## Table of Contents

1. [Introduction](#1-introduction)
2. [Key Concepts](#2-key-concepts)
   2.1. [Key Concepts](#21-Entity-Component-System (ECS))
3. [Classes](#3-classes)
   3.1. [Entity](#31-entity)
   3.2. [EntityManager](#32-entitymanager)
   3.3. [AComponent](#33-acomponent)
   3.4. [HealthComponent](#34-healthcomponent)
4. [Usage Example](#4-usage-example)
5. [Best Practices](#5-best-practices)
6. [Troubleshooting](#6-troubleshooting)
7. [FAQs](#7-faqs)

## 1. Introduction

Welcome to the Entity-Component-System (ECS) Developer Documentation for the RType architecture in C++. This ECS design allows you to create flexible and modular game entities using the entity-component pattern.

## 2. Key Concepts

### 2.1. Entity-Component-System (ECS)

ECS is a design pattern where entities are represented as compositions of components, and systems process these entities based on their components.

## 3. Classes

### 3.1. Entity

The `Entity` class represents an object in the system. It can have various components attached to it.

**Methods:**

- `getComponent<T>()`: Get a component of a specific type.
- `addComponent<T>(Args &&...args)`: Add a component of a specific type.
- `removeComponent<T>()`: Remove a component of a specific type.
- `updateComponents()`: Update all components associated with the entity.

### 3.2. EntityManager

The `EntityManager` class manages entities within the system.

**Methods:**

- `createEntity()`: Create and add a new entity.
- `destroyEntity(entity)`: Destroy and remove an entity.
- `updateEntities()`: Update all entities in the manager.

### 3.3. AComponent

The `AComponent` class is the base abstract class for components.

**Methods:**

- `update()`: Pure virtual function to be implemented by derived classes.

### 3.4. HealthComponent

The `HealthComponent` class is an example component derived from `AComponent`.

**Methods:**

- `setHealth(health)`: Set the health of the damageable entity.
- `getHealth()`: Get the health of the damageable entity.
- `update()`: Implementation of the base update function.

## 4. Usage Example

```cpp
// Sample usage of the ECS architecture

RType::EntityManager entityManager;

// Create entities and add components
RType::EntityPtr playerEntity = entityManager.createEntity();
playerEntity->addComponent<RType::HealthComponent>(100);

RType::EntityPtr enemyEntity = entityManager.createEntity();
enemyEntity->addComponent<RType::HealthComponent>(50);

// Update entities and components
entityManager.updateEntities();
```

5\. Best Practices
------------------

### Use components for specific functionalities (e.g., health, speed) to keep entities modular.

Organize your entities by attaching components that represent specific features or attributes, making them modular and easier to manage.

### Favor composition over inheritance for creating complex entities.

Instead of relying heavily on class inheritance, prefer composing entities with various components. This promotes flexibility and avoids issues related to deep class hierarchies.

### Update entities and components in a well-defined order to ensure proper dependencies are met.

Establish a clear update order for entities and their associated components to avoid conflicts and ensure that dependencies are satisfied during the update process.

6\. Troubleshooting
-------------------

### Ensure that components are properly defined and included in your project.

Double-check that all components are correctly implemented, and their headers are included in the relevant files. Ensure proper linkage and visibility.

### Check for any circular dependencies between components.

Circular dependencies can lead to compilation or runtime issues. Review the relationships between components to identify and resolve any circular dependencies.

7\. FAQs
--------

### Q: How do I add a new component to an entity?

A: Use the `addComponent<T>(Args &&...args)` method of the `Entity` class, providing the component type and constructor arguments. This method allows you to dynamically attach a specific type of component to an entity with the provided arguments.

### Q: How can I destroy an entity?

A: Call the `destroyEntity(entity)` method of the `EntityManager`, passing the entity you want to destroy. This method removes the specified entity from the system, ensuring proper cleanup and resource management.
