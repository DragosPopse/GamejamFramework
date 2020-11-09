﻿#include "EntityFactory.h"

using namespace jam::jecs;

EntityFactory::EntityFactory(SystemManager& manager) :
	_manager(manager)
{
}

EntityFactory::~EntityFactory() = default;

int32_t EntityFactory::Construct()
{
	_index = _manager.CreateEntity();
	OnConstruction();
	return _index;
}