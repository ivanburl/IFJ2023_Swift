//
// Created by burluiva on 11/30/2023.
//

#include "sem_analys.h"

Error semantic_analysis(GrammarToken *grammarToken) {

  for (int i=0;i<grammarToken->tokensHolderSize;i++) {
    Token* token = grammarToken->tokensHolder[i];
    if (token->type >= NON_TERMINAL_UNDEFINED) {
      semantic_analysis(grammarToken);
      grammarToken->grammarRule->sematicAnalysisFn();
    }
  }

}
