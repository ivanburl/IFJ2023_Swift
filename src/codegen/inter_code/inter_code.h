//
// Created by thekr on 11/21/2023.
//

#ifndef IFJ2023_SWIFT_INTER_CODE_H
#define IFJ2023_SWIFT_INTER_CODE_H
#include "ctype.h"
#include <stdio.h>
#include "../../model/grammar/rule/grammar_rule.h"

void InterCodeInit();
void InterCodeEnd();
void StoreString(int reg, String *str);
void StoreInt(int reg, long long i);
void StoreDouble(int reg, double d);
void ReadDouble(AddressCode *addressCode);
void ReadString(AddressCode *addressCode);
void ReadInt(AddressCode *addressCode);
void SumInterCode(AddressCode *addressCode);
void SubInterCode(AddressCode *addressCode);
void MulInterCode(AddressCode *addressCode);
void DivInterCode(AddressCode *addressCode);
void EqualInterCode(AddressCode *addressCode);
void NotEqualInterCode(AddressCode *addressCode);
void GreaterInterCode(AddressCode *addressCode);
void LessInterCode(AddressCode *addressCode);
void GreaterEqualInterCode(AddressCode *addressCode);
void LessEqualInterCode(AddressCode *addressCode);
void SoftUnwrapInterCode(AddressCode *addressCode);
void HardUnwrapInterCode(AddressCode *addressCode);
void Int2Double(AddressCode *addressCode);
void Double2Int(AddressCode *addressCode);
void func_length(AddressCode *addressCode);
void SubStringIntercode(AddressCode *addressCode);
void ord(AddressCode *addressCode);
void chr(AddressCode *addressCode);


//Write
//(not , a, , b ) … b := not(a)
//(goto, , , L1) … goto L1
//(goto, a, , L1) … if a = true then goto L1
//(lab , L1, , )… label L1:

#endif // IFJ2023_SWIFT_INTER_CODE_H