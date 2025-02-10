#pragma once

#include "API/APIHelper.h" // IWYU pragma: keep

#include <mc/world/actor/agent/Agent.h>

class AgentClass : public ScriptClass {
public:
    Agent* mAgent;

public:
    AgentClass(Agent* agent);

public:
    static Local<Object> newAgent(Agent* agent);

public: /* Member */
public: /* Method */
};

extern ClassDefine<AgentClass> agentClassBuilder;