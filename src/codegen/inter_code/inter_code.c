//
// Created by thekr on 11/21/2023.
//

#include "inter_code.h"

void InterCodeInit() {
  printf(".IFJcode23\n");
  printf("DEFVAR GF@FuncReturn");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  //InsertPrebuildFUNCS
}

void InterCodeEnd() {
  printf("LABEL ProgramEnd\n");
  printf("POPFRAME\n");
}

void PushArg(AddressCode *addressCode) {
  printf("PUSHS LF@r%d",addressCode->result);
}
//string - arg0
//od - arg1
//do - arg2
void SubStringIntercode(AddressCode *addressCode) {
  printf("DEFVAR TF@tempBool\n");
  printf("DEFVAR TF@arg2");
  printf("POPS TF@arg2");
  printf("DEFVAR TF@arg1");
  printf("POPS TF@arg1");
  printf("DEFVAR TF@arg0");
  printf("POPS TF@arg0");
  //i<0
  printf("LT TF@tempBool FL@arg1 int@0\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  //j<0
  printf("LT TF@tempBool FL@arg2 int@0\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  //i<j
  printf("GT TF@tempBool FL@arg1 FL@arg2\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  //strlen(s)
  printf("DEFVAR TF@TempInt\n");
  printf("STRLEN TF@TempInt FL@r%d\n",addressCode->result);
  //i>=strlen(s)
  printf("DEFVAR TF@TempBool1\n");
  printf("DEFVAR TF@TempBool2\n");
  printf("GT TF@tempBool1 FL@arg1 TF@TempInt\n");
  printf("EQ TF@tempBool2 FL@arg1 TF@TempInt\n");
  printf("OR TF@tempBool TF@tempBool1 TF@tempBool2\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  //j>strlen(s)
  printf("GT TF@tempBool FL@arg2 TF@TempInt\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  //*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*//
  //temps creations
  printf("DEFVAR TF@boolCycle\n");
  printf("DEFVAR TF@tempBoolCycle1\n");
  printf("DEFVAR TF@tempBoolCycle2\n");
  // (1*) int inc = i
  printf("DEFVAR TF@Increment\n");
  printf("MOVE TF@Increment FL@arg1\n");
  //substring and curchar def
  printf("DEFVAR TF@SubString\n");
  printf("MOVE TF@SubString string@\n");
  printf("DEFVAR TF@CurChar\n");
  //for( (1*) ; inc<=j; (2*) )
  printf("LABEL For_Head\n");
  printf("LT TF@tempBoolCycle1 TF@Increment FL@arg2\n");
  printf("EQ TF@tempBoolCycle2 TF@Increment FL@arg2\n");
  printf("OR TF@boolCycle TF@tempBoolCycle1 TF@tempBoolCycle2\n");
  printf("JUMPIFEQ For TF@boolCycle bool@true\n");
  //*-----*-----*-----*-----*-----*-----*-----*-----*-----*//
  //after For
  printf("MOVE LF@r%d TF@SubString\n",addressCode->result);
  printf("JUMP SubStringIntercodeEnd\n");
  //*-----*-----*-----*-----*-----*-----*-----*-----*-----*//
  printf("LABEL For\n");
  //code zone {
  //char c = arg0[inc];
  printf("GETCHAR TF@CurChar LF@arg0 TF@Increment\n");
  //string += c;
  printf("CONCAT TF@SubString TF@SubString TF@CurChar\n");
  // (2*)inc++
  printf("ADD TF@Increment TF@Increment int@1\n");
  //end of code zone }
  printf("JUMP For_Head\n");
  //*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*//
  printf("LABEL ReturnNil\n");
  printf("MOV LF@r%d nil@nil\n",addressCode->result);
  printf("LABEL SubStringIntercodeEnd\n");
}

//void InsertPrebuildFUNCS
//create readString
//arg1


// func ord(_ 𝑐 : String) -> Int – Vrátí ordinální hodnotu (ASCII) prvního znaku
// v řetězci 𝑐. Je-li řetězec prázdný, vrací funkce 0.
void ord(AddressCode *addressCode){
  printf("DEFVAR LF@r%d\n", addressCode->result);
//чекаем пустую строку
  printf("DEFVAR LF@len\n");
  printf("STRLEN LF@len LF@r%d\n",addressCode->result);
  printf("JUMPIFEQ ordEmpty LF@len int@0\n");
//первый символ значение получаем
  printf("DEFVAR LF@fchar\n");
  printf("GETCHAR LF@cfhar LF@r%d int@0\n", addressCode->result);
  printf("STRI2INT LF@r%d LF@fchar int@0\n", addressCode->result);
  printf("JUMP ordEnd\n");
//работаем с пустой строкой
  printf("LABEL ordEmpty\n");
  printf("MOVE LF@r%d int@0\n", addressCode->result);

  printf("LABEL ordEnd");
  //printf("JUMP ProgramEnd\n");
}

// func chr(_ 𝑖 : Int) -> String – Vrátí jednoznakový řetězec se znakem, jehož
// ASCII kód je zadán parametrem 𝑖. Hodnotu 𝑖 mimo interval[0; 255]řeší odpovídající instrukce IFJcode23.
void chr(AddressCode *addressCode){
  printf("DEFVAR LF@r%d\n", addressCode->result);
  // чукаем лежит ли в интервале 0-255
  printf("LT LF@Range int@0 LF@r%d\n", addressCode->op1);
  printf("JUMPIFEQ chrRange LF@Range bool@true\n");
  // ставим 0, если меньше 0
  printf("MOVE LF@r%d int@0\n", addressCode->result);
  printf("JUMP chrend\n");
  printf("LABEL chrRange\n");
  printf("GT LF@chRange LF@r%d int@255\n", addressCode->op1);
  printf("JUMPIFEQ chrRange LF@Range bool@true\n");
  //ставим 255 если больше 255
  printf("MOVE LF@r%d int@255\n", addressCode->result);
// конвертуем в символ
  printf("INT2CHAR LF@r%d LF@r%d\n", addressCode->op1, addressCode->result);
  printf("LABEL chrend\n");
}

//func readString() -> String?
void ReadString(AddressCode *addressCode){
  printf("DEFVAR LF@r%d\n", addressCode->result);
  printf("READ LF@r%d string\n", addressCode->result);
}

//func readInt() -> Int?
void ReadInt(AddressCode *addressCode){
  printf("DEFVAR LF@r%d\n", addressCode->result);
  printf("READ LF@r%d int\n", addressCode->result);
}

//call ReadDouble
//func readDouble() -> Double?
void ReadDouble(AddressCode *addressCode){
  //jump end of double
  //ReadDouble:

  printf("DEFVAR LF@r%d\n", addressCode->result);
  printf("READ LF@r%d double\n", addressCode->result);

  //return
  //end of double:
}
// func Int2Double(_ term ∶ Int) -> Double – Vrátí hodnotu celočíselného termu
// term konvertovanou na desetinné číslo. Pro konverzi z celého čísla využijte odpovídající instrukci z IFJcode23.
void Int2Double(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("INT2FLOAT LF@r%d LF@r%d\n", addressCode->result, addressCode->op1);
}
// func Double2Int(_ term ∶ Double) -> Int – Vrátí hodnotu desetinného termu
// term konvertovanou na celé číslo, a to oříznutím desetinné části. Pro konverzi z desetinného čísla využijte odpovídající instrukci z IFJcode23.
void Double2Int(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("FLOAT2INT LF@r%d LF@r%d\n", addressCode->result, addressCode->op1);
}
// func length(_ 𝑠 : String) -> Int – Vrátí délku (počet znaků) řetězce 𝑠. Např.
// length("x\nz") vrací 3.
void func_length(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("STRLEN LF@r%d LF@r%d\n", addressCode->result,addressCode->op1);
}


//op1 = int to store
//res = register to store
void StoreInt(int reg, long long i) {
  printf("DEFVAR LF@r%d\n",reg);
  if (i == -1) {
    printf("MOVE LF@r%d nil@nil\n",reg);
  } else {
    printf("MOVE LF@r%d int@%lld\n",reg,i);
  }
}

void StoreDouble(int reg, double d) {
  printf("DEFVAR LF@r%d\n",reg);
  if (d == -1) {
    printf("MOVE LF@r%d nil@nil\n",reg);
  } else {
    printf("MOVE LF@r%d float@%a\n",reg,d);
  }
}

void StoreBool(int reg,bool b ){
  printf("DEFVAR LF@r%d\n", reg);
  if (b == false) {
    printf("MOVE LF@r%d nil@nil\n",reg);
  } else {
    printf("MOVE LF@r%d bool@%d\n",reg,b);
  }
}



//typedef struct string {
//  size_t length;
//  char *data;
//} String;
void StoreString(int reg, String *str) {
  printf("DEFVAR LF@r%d\n",reg);
  if (str->length == 0) {
    printf("MOVE LF@r%d nil@nil\n",reg);
  } else {
    printf("MOVE LF@r%d string@\n",reg);
    printf("DEFVAR TF@temp\n");
    printf("DEFVAR TF@tempSymb\n");
    for (int i = 0; i < str->length; i++) {
      if (isalpha(str->data[i])) {
        printf("MOVE TF@temp string@%c\n", str->data[i]);
        printf("CONCAT LF@r%d LF@r%d TF@temp\n", reg, reg);
      } else {
        printf("MOVE TF@temp string@%c\n", str->data[i]);
        printf("STRI2INT TF@tempSymb TF@temp int@0\n");
        printf("CONCAT LF@r%d LF@r%d string@\\\n", reg, reg);
        printf("CONCAT LF@r%d LF@r%d TF@tempSymb\n", reg, reg);
      }
    }
  }
}

void OrInterCode(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("OR LF@r%d LF@r%d LF@r%d\n",addressCode->result,addressCode->op1,addressCode->op2);
}

void AndInterCode(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("AND LF@r%d LF@r%d LF@r%d\n",addressCode->result,addressCode->op1,addressCode->op2);
}

void SumInterCode(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("ADD LF@r%d LF@r%d LF@r%d\n",addressCode->result,addressCode->op1,addressCode->op2);
}

void SubInterCode(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("SUB LF@r%d LF@r%d LF@r%d\n",addressCode->result,addressCode->op1,addressCode->op2);
}

void MulInterCode(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("MUL LF@r%d LF@r%d LF@r%d\n",addressCode->result,addressCode->op1,addressCode->op2);
}

void DivInterCode(AddressCode *addressCode) {
  printf("DEFVAR TF@temp1\n");
  printf("DEFVAR TF@temp2\n");
  printf("INT2FLOAT TF@temp1 LF@r%d\n",addressCode->op1);
  printf("INT2FLOAT TF@temp2 LF@r%d\n",addressCode->op2);
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("DIV LF@r%d TF@temp1 TF@temp2\n",addressCode->result);
}

void EqualInterCode(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("EQ LF@r%d LF@r%d LF@r%d\n",addressCode->result,addressCode->op1, addressCode->op2);
}

void NotEqualInterCode(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("JUMPIFNEQ NotEqual LF@r%d LF@r%d\n", addressCode->op1, addressCode->op2);
  printf("MOVE LF@r%d bool@false\n",addressCode->result);
  printf("JUMP NotEqualInterCodeEnd\n");

  printf("LABEL NotEqual\n");
  printf("MOVE LF@r%d bool@true\n",addressCode->result);
  printf("LABEL NotEqualInterCodeEnd\n");
}

void GreaterInterCode(AddressCode *addressCode) {
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("GT LF@r%d LF@r%d LF@r%d\n",addressCode->result,addressCode->op1, addressCode->op2);
}

void LessInterCode(AddressCode *addressCode){
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("LT LF@r%d LF@r%d LF@r%d\n",addressCode->result,addressCode->op1, addressCode->op2);
}

void GreaterEqualInterCode(AddressCode *addressCode) {
  printf("DEFVAR TF@tempBool0\n");
  printf("GT TF@tempBool0 LF@r%d LF@r%d\n",addressCode->op1, addressCode->op2);
  printf("DEFVAR TF@tempBool1\n");
  printf("EQ TF@tempBool1 LF@r%d LF@r%d\n",addressCode->op1, addressCode->op2);
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("OR LF@r%d TF@tempBool0 TF@tempBool1\n",addressCode->result);
}

void LessEqualInterCode(AddressCode *addressCode) {
  printf("DEFVAR TF@tempBool0\n");
  printf("LT TF@tempBool0 LF@r%d LF@r%d\n",addressCode->op1, addressCode->op2);
  printf("DEFVAR TF@tempBool1\n");
  printf("EQ TF@tempBool1 LF@r%d LF@r%d\n",addressCode->op1, addressCode->op2);
  printf("DEFVAR LF@r%d\n",addressCode->result);
  printf("OR LF@r%d TF@tempBool0 TF@tempBool1\n",addressCode->result);
}

//op1 - starting number
//op2 - what it should be equal to if op1 is NULL
//result - resulting number
void SoftUnwrapInterCode(AddressCode *addressCode) {
  if (addressCode->op1 == -1) {
    printf("DEFVAR LF@r%d\n",addressCode->result);
    printf("MOVE LF@r%d LF@r%d\n",addressCode->result,addressCode->op2);
  }
}

//void HardUnwrapInterCode(AddressCode *addressCode) {
//  if (addressCode->op1 == -1) {
//    printf("EXIT 99\n");
//  }

void WhileInitInterCode(AddressCode *addressCode){
  printf("LABEL WHILE%d\n", addressCode->result);
}

void CondWhileInterCode (AddressCode *addressCode){
  printf("JUMPIFEQ BLOCK%d LF@r%d bool@true\n",addressCode->result,addressCode->op1);
  printf("JUMPIFEQ ESCAPE%d LF@r%d bool@false\n",addressCode->result,addressCode->op1);
  printf("LABEL BLOCK%d\n",addressCode->result);
}

void geBlockWhileInterCode (AddressCode *addressCode){
  printf("JUMP WHILE%d\n",addressCode->result);
  printf("LABEL ESCAPE%d\n",addressCode->result);
}

void GenerateFunctionInterCode(AddressCode *addressCode) {
  printf("LABEL Fun%d\n", addressCode->op1);
//обработка параметров
  printf("JUMP CodeBlockF%d\n",addressCode->op1);
//блок функции
  printf("LABEL ReturnFunc%d\n",addressCode->op1);
  printf("RETURN\n");
}

//короче тут вообще хз, сильно на меня не матерись я уже заебанный пишу это
void GenerateBlock(AddressCode *addressCode){
  printf("LABEL CodeBlocklock%d\n", addressCode->op1);
  printf("DEFVAR LF@tempVar\n");

  printf("JUMPZ EndCodeBlock%d LF@tempVar\n", addressCode->op1);//короче тут хз еще тип если что то сиганет в конец

  printf("WRITE LF@tempVar\n");// Код, который будет выполнен, если все заебись

  printf("LABEL EndCodeBlock%d\n", addressCode->op1);
}
