#include "API/Mob/Agent.h"


ClassDefine<AgentClass> agentClassBuilder = defineClass<AgentClass>("Agent")
                                                .constructor(nullptr)

                                                .build();

AgentClass::AgentClass(Agent* agent) : ScriptClass(ConstructFromCpp<AgentClass>{}) { this->mAgent = agent; }

Local<Object> AgentClass::newAgent(Agent* agent) { return (new AgentClass(agent))->getScriptObject(); }
