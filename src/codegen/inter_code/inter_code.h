//
// Created by thekr on 11/21/2023.
//

#ifndef IFJ2023_SWIFT_INTER_CODE_H
#define IFJ2023_SWIFT_INTER_CODE_H
#include "../../model/grammar/rule/grammar_rule.h"
#include "../../model/grammar/token/grammar_token.h"
#include "ctype.h"
#include "stdbool.h"
#include <stdio.h>

void InterCodeInit();
void InterCodeEnd();
void StoreString(GrammarToken *grammarToken, AddressTable *addressTable);
void StoreInt(GrammarToken *grammarToken, AddressTable *addressTable);
void StoreDouble(GrammarToken *grammarToken, AddressTable *addressTable);
void ReadDouble();
void ReadString();
void ReadInt();
void StoreBool(GrammarToken *grammarToken, AddressTable *addressTable);
void SumInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void SubInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void MulInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void DivInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void EqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void NotEqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void GreaterInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void LessInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void GreaterEqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void LessEqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void SoftUnwrapInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
//void HardUnwrapInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void OrInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void AndInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void Int2Double(GrammarToken *grammarToken, AddressTable *addressTable);
void Double2Int(GrammarToken *grammarToken, AddressTable *addressTable);
void StrLength(GrammarToken *grammarToken, AddressTable *addressTable);
void SubStringIntercode();
void ord(GrammarToken *grammarToken, AddressTable *addressTable);
void chr(GrammarToken *grammarToken, AddressTable *addressTable);
void WhileInitInterCode(GrammarToken *grammarToken, AddressTable *addressTable);
void CondWhileInterCode (GrammarToken *grammarToken, AddressTable *addressTable);
void BlockWhileInterCode (GrammarToken *grammarToken, AddressTable *addressTable);
void GetF(GrammarToken *grammarToken, AddressTable *addressTable);


//Write
//(not , a, , b ) … b := not(a)
//(goto, , , L1) … goto L1
//(goto, a, , L1) … if a = true then goto L1
//(lab , L1, , )… label L1:

#endif // IFJ2023_SWIFT_INTER_CODE_H
