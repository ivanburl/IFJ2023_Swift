//
// Created by burluiva on 10/12/2023.
//

#include "automata.h"

#define AUTOMATA_STATE_ASSERT(T) assert(T>=0 && T<MAX_AUTOMATA_STATES_NUMBER)

#define AUTOMATA_EDGE_ASSERT(T) assert(T>=0 && T<MAX_AUTOMATA_EDGE_TYPES)

void automata_init(Automata *automata, int startState,
                   int defaultStateReturnValue) {
  assert(automata);

  automata->currentState = startState;
  automata->startState = startState;
  automata->defaultStateReturnValue = defaultStateReturnValue;

  for (int i = 0; i < MAX_AUTOMATA_STATES_NUMBER; i++) {
    for (int j = 0; j < MAX_AUTOMATA_EDGE_TYPES; j++) {
      automata->automata[i][j] = startState;
    }
    automata->stateReturnValues[i] = defaultStateReturnValue;
  }
}

void automata_set_edge(Automata *automata, int fromState, int edgeType, int toState) {
  assert(automata);
  AUTOMATA_STATE_ASSERT(fromState);
  AUTOMATA_STATE_ASSERT(toState);
  AUTOMATA_EDGE_ASSERT(edgeType);

  automata->automata[fromState][edgeType] = toState;
}

int automata_get_stateReturnValue(Automata *automata, int state) {
  assert(automata);
  AUTOMATA_STATE_ASSERT(state);
  return automata->stateReturnValues[state];
}

void automata_set_stateReturnValue(Automata *automata, int state, int returnValue) {
  assert(automata);
  AUTOMATA_STATE_ASSERT(state);
  automata->stateReturnValues[state] = returnValue;
}

void automata_next_state(Automata *automata, int edgeType) {
  assert(automata);
  AUTOMATA_EDGE_ASSERT(edgeType);
  automata->currentState = automata->automata[automata->currentState][edgeType];
}