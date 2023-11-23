//
// Created by thekr on 11/21/2023.
//

#include "inter_code.h"

void InterCodeInit() {
  printf(".IFJcode23\n");
  printf("DEFVAR GF@FuncReturn\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  InitPrebuildFunc();
  //InsertPrebuildFUNCS
}

void InitPrebuildFunc() {
  SubStringIntercode();
  chr();

}

void InterCodeEnd() {
  printf("LABEL ProgramEnd\n");
  printf("POPFRAME\n");
}
//ARG, NULL, (TokenType[]){E, ARG_TMP
void PushArg(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("PUSHS LF@r%d\n", grammarToken->tokensHolder[0]->data.grammarToken->reg);
}

void GetF(GrammarToken *grammarToken, AddressTable *addressTable) {
  grammarToken->reg = grammarToken->tokensHolder[0]->data.grammarToken->reg;
}
//string - arg0
//od - arg1
//do - arg2
void SubStringIntercode() {
  printf("JUMP SubstringIntercodeEnd\n");
  printf("LABEL Substring\n");
  printf("DEFVAR TF@tempBool\n");
  printf("DEFVAR TF@arg2\n");
  printf("POPS TF@arg2\n");
  printf("DEFVAR TF@arg1\n");
  printf("POPS TF@arg1\n");
  printf("DEFVAR TF@arg0\n");
  printf("POPS TF@arg0\n");
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
  printf("STRLEN TF@TempInt GF@FuncReturn\n");
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
  printf("MOVE GF@FuncReturn TF@SubString\n");
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
  printf("MOV GF@FuncReturn nil@nil\n");

  printf("LABEL SubStringIntercodeEnd\n");
}

//void InsertPrebuildFUNCS
//create readString
//arg1


// func ord(_ 𝑐 : String) -> Int – Vrátí ordinální hodnotu (ASCII) prvního znaku
// v řetězci 𝑐. Je-li řetězec prázdný, vrací funkce 0.
void ord(){
  printf("JUMP ordend");
  printf("LABEL ord");
  printf("DEFVAR LF@r%d\n");
//чекаем пустую строку
  printf("DEFVAR LF@len\n");
  printf("STRLEN LF@len LF@r%d\n");
  printf("JUMPIFEQ ordEmpty LF@len int@0\n");
//первый символ значение получаем
  printf("DEFVAR LF@fchar\n");
  printf("GETCHAR LF@cfhar LF@r%d int@0\n");
  printf("STRI2INT LF@r%d LF@fchar int@0\n");
  printf("JUMP ordEnd\n");
//работаем с пустой строкой
  printf("LABEL ordEmpty\n");
  printf("RETURN\n");
  printf("MOVE LF@r%d int@0\n");

  printf("LABEL ordEnd");
}

// func chr(_ 𝑖 : Int) -> String – Vrátí jednoznakový řetězec se znakem, jehož
// ASCII kód je zadán parametrem 𝑖. Hodnotu 𝑖 mimo interval[0; 255]řeší odpovídající instrukce IFJcode23.
void chr(){
  printf("JUMP chrend");
  printf("LABEL chr");
  printf("DEFVAR LF@r%d\n");
  // чукаем лежит ли в интервале 0-255
  printf("LT LF@Range int@0 LF@r%d\n");
  printf("JUMPIFEQ chrRange LF@Range bool@true\n");
  // ставим 0, если меньше 0
  printf("MOVE LF@r%d int@0\n");
  printf("JUMP chrend\n");
  printf("LABEL chrRange\n");
  printf("GT LF@chRange LF@r%d int@255\n");
  printf("JUMPIFEQ chrRange LF@Range bool@true\n");
  //ставим 255 если больше 255
  printf("MOVE LF@r%d int@255\n");
// конвертуем в символ
  printf("INT2CHAR LF@r%d LF@r%d\n");
  printf("RETURN");
  printf("LABEL chrend\n");
}


//func readString() -> String?
void ReadString(){
  printf("JUMP readStringEnd\n");
  printf("LABEL readString\n");
  printf("READ GF@FuncReturn string\n");
  printf("LABEL readStringEnd")
}


//func readInt() -> Int?
void ReadInt(){
  printf("JUMP ReadIntEnd\n");
  printf("LABEL readInt\n");
  printf("READ GF@FuncREturn int\n");
  printf ("LABEL ReadIntEnd");
}


//call ReadDouble
//func readDouble() -> Double?
void ReadDouble(){
  printf("JUMP readDoubleEnd\n");
  printf("LABEL readDouble\n");
  printf("READ GF@FuncRetur double\n");
  printf("LABEL readDoubleEnd")

}


// func Int2Double(_ term ∶ Int) -> Double – Vrátí hodnotu celočíselného termu
// term konvertovanou na desetinné číslo. Pro konverzi z celého čísla využijte odpovídající instrukci z IFJcode23.
void Int2Double() {
  printf("JUMP ReadIntEnd\n");
  printf("LABEL readInt\n");
  printf("INT2FLOAT LF@r%d LF@r%d\n");
}


// func Double2Int(_ term ∶ Double) -> Int – Vrátí hodnotu desetinného termu
// term konvertovanou na celé číslo, a to oříznutím desetinné části. Pro konverzi z desetinného čísla využijte odpovídající instrukci z IFJcode23.
void Double2Int(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n",res);
  printf("FLOAT2INT LF@r%d LF@r%d\n", res, grammarToken->tokensHolder[0]->data.grammarToken->reg);
}


// func length(_ 𝑠 : String) -> Int – Vrátí délku (počet znaků) řetězce 𝑠. Např.
// length("x\nz") vrací 3.
void StrLength(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n",res);
  printf("STRLEN LF@r%d LF@r%d\n", res,grammarToken->tokensHolder[0]->data.grammarToken->reg);
}


//op1 = int to store
//res = register to store
void StoreInt(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("DEFVAR LF@r%d\n", get_reg_new(addressTable));
  printf("MOVE LF@r%d int@%lld\n", get_reg_cur(addressTable), grammarToken->tokensHolder[0]->data.integer_value);
  grammarToken->reg = get_reg_cur(addressTable);
}

void StoreDouble(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("DEFVAR LF@r%d\n", get_reg_new(addressTable));
  printf("MOVE LF@r%d float@%a\n", get_reg_cur(addressTable), grammarToken->tokensHolder[0]->data.double_value);
  grammarToken->reg = get_reg_cur(addressTable);
}

void StoreBool(GrammarToken *grammarToken, AddressTable *addressTable){
  printf("DEFVAR LF@r%d\n", get_reg_new(addressTable));
  if (grammarToken->tokensHolder[0]->data.integer_value) {
    printf("MOVE LF@r%d bool@true\n", get_reg_cur(addressTable));
  } else {
    printf("MOVE LF@r%d bool@false\n", get_reg_cur(addressTable));
  }
  grammarToken->reg = get_reg_cur(addressTable);
}



//typedef struct string {
//  size_t length;
//  char *data;
//} String;
void StoreString(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("DEFVAR LF@r%d\n", get_reg_new(addressTable));
  if (grammarToken->tokensHolder[0]->data.string.length == 0) {
    printf("MOVE LF@r%d nil@nil\n", get_reg_cur(addressTable));
  } else {
    printf("MOVE LF@r%d string@\n",get_reg_cur(addressTable));
    printf("DEFVAR TF@temp\n");
    printf("DEFVAR TF@tempSymb\n");
    for (int i = 0; i < grammarToken->tokensHolder[0]->data.string.length; i++) {
      if (isalpha(grammarToken->tokensHolder[0]->data.string.data[i])) {
        printf("MOVE TF@temp string@%c\n", grammarToken->tokensHolder[0]->data.string.data[i]);
        printf("CONCAT LF@r%d LF@r%d TF@temp\n",get_reg_cur(addressTable),get_reg_cur(addressTable));
      } else {
        printf("MOVE TF@temp string@%c\n", grammarToken->tokensHolder[0]->data.string.data[i]);
        printf("STRI2INT TF@tempSymb TF@temp int@0\n");
        printf("CONCAT LF@r%d LF@r%d string@\\\n",get_reg_cur(addressTable),get_reg_cur(addressTable));
        printf("CONCAT LF@r%d LF@r%d TF@tempSymb\n",get_reg_cur(addressTable),get_reg_cur(addressTable));
      }
    }
  }
  grammarToken->reg = get_reg_cur(addressTable);
}

void OrInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n",res);
  printf("OR LF@r%d LF@r%d LF@r%d\n",res,
                                        grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                        grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void AndInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n",res);
  printf("AND LF@r%d LF@r%d LF@r%d\n",res,
                                          grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                          grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

//{E, PLUS, E}
// E -> {F}
//GrammarToken -> {TOKEN, TOKEN, TOKEN, ...}
//TOKEN -> GrammarToken
void SumInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n", res);
  printf("ADD LF@r%d LF@r%d LF@r%d\n", res,
                                      grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                      grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void SubInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n", res);
  printf("SUB LF@r%d LF@r%d LF@r%d\n",res,
                                      grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                      grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void MulInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n", res);
  printf("MUL LF@r%d LF@r%d LF@r%d\n",res,
                                      grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                      grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void DivInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR TF@temp1\n");
  printf("DEFVAR TF@temp2\n");
  printf("INT2FLOAT TF@temp1 LF@r%d\n",grammarToken->tokensHolder[0]->data.grammarToken->reg);
  printf("INT2FLOAT TF@temp2 LF@r%d\n",grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("DEFVAR LF@r%d\n",res);
  printf("DIV LF@r%d TF@temp1 TF@temp2\n",res);
  grammarToken->reg = get_reg_cur(addressTable);
}

void EqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n",res);
  printf("EQ LF@r%d LF@r%d LF@r%d\n",res,
                                     grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                     grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void NotEqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n",res);
  printf("JUMPIFNEQ NotEqual LF@r%d LF@r%d\n",grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                              grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("MOVE LF@r%d bool@false\n",res);
  printf("JUMP NotEqualInterCodeEnd\n");

  printf("LABEL NotEqual\n");
  printf("MOVE LF@r%d bool@true\n",res);
  printf("LABEL NotEqualInterCodeEnd\n");
  grammarToken->reg = get_reg_cur(addressTable);
}

void GreaterInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n",res);
  printf("GT LF@r%d LF@r%d LF@r%d\n",res,
                                     grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                     grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void LessInterCode(GrammarToken *grammarToken, AddressTable *addressTable){
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n",res);
  printf("LT LF@r%d LF@r%d LF@r%d\n",res,
                                     grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                     grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void GreaterEqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR TF@tempBool0\n");
  printf("GT TF@tempBool0 LF@r%d LF@r%d\n",
                                          grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                          grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("DEFVAR TF@tempBool1\n");
  printf("EQ TF@tempBool1 LF@r%d LF@r%d\n",
                                          grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                          grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("DEFVAR LF@r%d\n",res);
  printf("OR LF@r%d TF@tempBool0 TF@tempBool1\n",res);
  grammarToken->reg = get_reg_cur(addressTable);
}

void LessEqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR TF@tempBool0\n");
  printf("LT TF@tempBool0 LF@r%d LF@r%d\n",
                                          grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                          grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("DEFVAR TF@tempBool1\n");
  printf("EQ TF@tempBool1 LF@r%d LF@r%d\n",
                                          grammarToken->tokensHolder[0]->data.grammarToken->reg,
                                          grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("DEFVAR LF@r%d\n",res);
  printf("OR LF@r%d TF@tempBool0 TF@tempBool1\n",res);
  grammarToken->reg = get_reg_cur(addressTable);
}

//op1 - starting number
//op2 - what it should be equal to if op1 is NULL
//result - resulting number
void SoftUnwrapInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  if (grammarToken->tokensHolder[0]->data.grammarToken->reg == -1) {
    printf("DEFVAR LF@r%d\n",res);
    printf("MOVE LF@r%d LF@r%d\n",res,grammarToken->tokensHolder[2]->data.grammarToken->reg);
  }
  grammarToken->reg = get_reg_cur(addressTable);
}

//void HardUnwrapInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
//  if (addressCode->op1 == -1) {
//    printf("EXIT 99\n");
//  }

/*
void WhileInitInterCode(AddressCode *addressCode){
  printf("LABEL cycle%d\n", addressCode->result);
}

void CondWhileInterCode (AddressCode *addressCode){
  printf("JUMPIFEQ BLOCK%d LF@r%d bool@true\n",addressCode->result,addressCode->op1);
  printf("JUMPIFEQ ESCAPE%d LF@r%d bool@false\n",addressCode->result,addressCode->op1);
  printf("LABEL BLOCK%d\n",addressCode->result);
}

void geBlockWhileInterCode (AddressCode *addressCode){
  printf("JUMP cycle%d\n",addressCode->result);
  printf("LABEL ESCAPE%d\n",addressCode->result);
}

void GenerateFunctionInterCode(AddressCode *addressCode) {
  printf("LABEL Fun%d\n",addressCode->op1);
//обработка параметров
//  printf("JUMP CodeBlock%d\n",addressCode->op1);
//блок функции
//  printf("LABEL ReturnFunc%d\n",addressCode->op1);
  printf("RETURN\n");
}

void GenerateIfInterCode (AddressCode *addressCode) {
  printf("LABEL If%d\n",addressCode->op1);
  printf("JUMPIFEQ CodeBlock%d LF@r%d bool@true\n",addressCode->op1,addressCode->op2);
  printf("LABEL Else%d\n",addressCode->result);
  printf("JUMP CodeBlock%d\n",addressCode->result);
}

void GenerateCodeBlock(int blockID,int argCount){
  for (int i = 0; i < argCount; i++) {
    printf("POPS TF@arg%d\n",argCount);
  }
  printf("LABEL CodeBlocklock%d\n", blockID);
  printf("DEFVAR LF@tempVar\n");

  printf("JUMPIFEQ EndCodeBlock%d LF@tempVar bool@true\n", blockID);//короче тут хз еще тип если что то сиганет в конец

  printf("LABEL EndCodeBlock%d\n", blockID);
}

void IfGeneration(AddressCode *addressCode) {

}
*/