////
//// Created by thekr on 11/21/2023.
////
//
//#ifndef IFJ2023_SWIFT_INTER_CODE_H
//#define IFJ2023_SWIFT_INTER_CODE_H
//#include "../../model/grammar/rule/grammar_rule.h"
//#include "../../model/grammar/token/grammar_token.h"
//#include "ctype.h"
//#include "stdbool.h"
//#include <stdio.h>
//
//void InterCodeInit();
//void InterCodeEnd();
//void StoreString(int reg, String *str);
//void StoreInt(int reg, long long i);
//void StoreDouble(int reg, double d);
//void ReadDouble(GrammarToken *grammarToken, AddressTable *addressTable);
//void ReadString(AddressCode *addressCode);
//void ReadInt(AddressCode *addressCode);
//void StoreBool(int reg,bool b );
//void SumInterCode(AddressCode *addressCode);
//void SubInterCode(AddressCode *addressCode);
//void MulInterCode(AddressCode *addressCode);
//void DivInterCode(AddressCode *addressCode);
//void EqualInterCode(AddressCode *addressCode);
//void NotEqualInterCode(AddressCode *addressCode);
//void GreaterInterCode(AddressCode *addressCode);
//void LessInterCode(AddressCode *addressCode);
//void GreaterEqualInterCode(AddressCode *addressCode);
//void LessEqualInterCode(AddressCode *addressCode);
//void SoftUnwrapInterCode(AddressCode *addressCode);
//void HardUnwrapInterCode(AddressCode *addressCode);
//void Int2Double(AddressCode *addressCode);
//void Double2Int(AddressCode *addressCode);
//void func_length(AddressCode *addressCode);
//void SubStringIntercode(AddressCode *addressCode);
//void ord(AddressCode *addressCode);
//void chr(AddressCode *addressCode);
//void OrInterCode(AddressCode *addressCode);
//void AndInterCode(AddressCode *addressCode);
//void WhileInitInterCode(AddressCode *addressCode);
//void CondWhileInterCode (AddressCode *addressCode);
//void BlockWhileInterCode (AddressCode *addressCode);
//
//
////Write
////(not , a, , b ) … b := not(a)
////(goto, , , L1) … goto L1
////(goto, a, , L1) … if a = true then goto L1
////(lab , L1, , )… label L1:
//
//#endif // IFJ2023_SWIFT_INTER_CODE_H

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
