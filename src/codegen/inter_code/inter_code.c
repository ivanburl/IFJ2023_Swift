#include "inter_code.h"

char* registerPrefixGen(bool isGlobal) {
  return isGlobal ? "GF" : "LF";
}

void InterCodeInit() {
  printf(".IFJcode23\n");
  printf("DEFVAR GF@FuncReturn\n");
  printf("MOVE GF@FuncReturn nil@nil\n");
  printf("DEFVAR GF@__ArgCount__\n");
  printf("MOVE GF@__ArgCount__ nil@nil\n");
  printf("DEFVAR GF@__Arg__\n");
  printf("MOVE GF@__Arg__ nil@nil\n");
  InitPrebuildFunc();
  // InsertPrebuildFUNCS
}

void InitPrebuildFunc() {
 // SubStringIntercode();
 // Chr();
  Ord();
 // ReadString();
 // ReadInt();
 // ReadDouble();
 // Int2Double();
 // Double2Int();
 // StrLength();
  Write();
}

void InterCodeEnd() {
  printf("LABEL ProgramEnd\n");
  printf("POPFRAME\n");
}
// ARG, NULL, (TokenType[]){E, ARG_TMP

void GetF(GrammarToken *grammarToken, AddressTable *addressTable) {
  grammarToken->reg = grammarToken->tokensHolder[0]->data.grammarToken->reg;
  grammarToken->isGlobal = grammarToken->tokensHolder[0]->data.grammarToken->isGlobal;
}

// string - arg0
// od - arg1
// do - arg2
void SubStringIntercode() {
  printf("JUMP SubstringIntercodeEnd\n");
  printf("LABEL Substring\n");
  printf("CREATEFRAME");
  printf("PUSHFRAME");
  printf("DEFVAR TF@tempBool\n");
  printf("DEFVAR TF@arg2\n");
  printf("POPS TF@arg2\n");
  printf("DEFVAR TF@arg1\n");
  printf("POPS TF@arg1\n");
  printf("DEFVAR TF@arg0\n");
  printf("POPS TF@arg0\n");
  // i<0
  printf("LT TF@tempBool TF@arg1 int@0\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  // j<0
  printf("LT TF@tempBool TF@arg2 int@0\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  // i<j
  printf("GT TF@tempBool TF@arg1 TF@arg2\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  // strlen(s)
  printf("DEFVAR TF@TempInt\n");
  printf("STRLEN TF@TempInt GF@FuncReturn\n");
  // i>=strlen(s)
  printf("DEFVAR TF@TempBool1\n");
  printf("DEFVAR TF@TempBool2\n");
  printf("GT TF@tempBool1 TF@arg1 TF@TempInt\n");
  printf("EQ TF@tempBool2 TF@arg1 TF@TempInt\n");
  printf("OR TF@tempBool TF@tempBool1 TF@tempBool2\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  // j>strlen(s)
  printf("GT TF@tempBool TF@arg2 TF@TempInt\n");
  printf("JUMPIFEQ ReturnNil TF@tempBool bool@true\n");
  //*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*//
  // temps creations
  printf("DEFVAR TF@boolCycle\n");
  printf("DEFVAR TF@tempBoolCycle1\n");
  printf("DEFVAR TF@tempBoolCycle2\n");
  // (1*) int inc = i
  printf("DEFVAR TF@Increment\n");
  printf("MOVE TF@Increment TF@arg1\n");
  // substring and curchar def
  printf("DEFVAR TF@SubString\n");
  printf("MOVE TF@SubString string@\n");
  printf("DEFVAR TF@CurChar\n");
  // for( (1*) ; inc<=j; (2*) )
  printf("LABEL For_Head\n");
  printf("LT TF@tempBoolCycle1 TF@Increment TF@arg2\n");
  printf("EQ TF@tempBoolCycle2 TF@Increment TF@arg2\n");
  printf("OR TF@boolCycle TF@tempBoolCycle1 TF@tempBoolCycle2\n");
  printf("JUMPIFEQ For TF@boolCycle bool@true\n");
  //*-----*-----*-----*-----*-----*-----*-----*-----*-----*//
  // after For
  printf("MOVE GF@FuncReturn TF@SubString\n");
  printf("RETURN\n");
  //*-----*-----*-----*-----*-----*-----*-----*-----*-----*//
  printf("LABEL For\n");
  // code zone {
  // char c = arg0[inc];
  printf("GETCHAR TF@CurChar LF@arg0 TF@Increment\n");
  // string += c;
  printf("CONCAT TF@SubString TF@SubString TF@CurChar\n");
  // (2*)inc++
  printf("ADD TF@Increment TF@Increment int@1\n");
  // end of code zone }
  printf("JUMP For_Head\n");
  //*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*-----*//
  printf("LABEL ReturnNil\n");
  printf("MOV GF@FuncReturn nil@nil\n");
  printf("RETURN\n");
  printf("LABEL SubStringIntercodeEnd\n");
}

// void InsertPrebuildFUNCS
// create readString
// arg1

// func ord(_ 𝑐 : String) -> Int – Vrátí ordinální hodnotu (ASCII) prvního znaku
// v řetězci 𝑐. Je-li řetězec prázdný, vrací funkce 0.
void Ord() {
  printf("JUMP ordEnd\n");
  printf("LABEL ord\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");

  printf("DEFVAR LF@$ARG_LEN\n");
  printf("POPS LF@$ARG_LEN\n");

  printf("DEFVAR LF@str\n");
  printf("DEFVAR LF@strlen\n");
  printf("POPS LF@str\n");
  printf("STRLEN LF@strlen LF@str\n");
  printf("JUMPIFEQ IfLinezero LF@strlen int@0\n");
  printf("STRI2INT LF@strlen LF@str int@0\n");
  printf("POPFRAME\n");
  printf("MOVE GF@FuncReturn TF@strlen\n");
  printf("RETURN\n");
  printf("LABEL IfLinezero\n");
  //*----*----*----*----*----*----*----*----*//
  printf("POPFRAME\n");
  printf("MOVE GF@FuncReturn nil@nil\n");
  printf("RETURN\n");
  //*----*----*----*----*----*----*----*----*//
  printf("LABEL ordEnd\n");
}

// func chr(_ 𝑖 : Int) -> String – Vrátí jednoznakový řetězec se znakem, jehož
// ASCII kód je zadán parametrem 𝑖. Hodnotu 𝑖 mimo interval[0; 255]řeší
// odpovídající instrukce IFJcode23.
void Chr() {

  printf("JUMP chrend\n");
  printf("LABEL chr\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  printf("DEFVAR LF@$ARG_LEN\n");
  printf("POPS LF@$ARG_LEN\n");
  printf("DEFVAR LF@number\n");
  printf("DEFVAR LF@strlen\n");
  printf("MOVE LF@strlen string@a\n");
  printf("POPS LF@number\n");
  printf("INT2CHAR LF@strlen LF@number\n");
  printf("POPFRAME\n");
  printf("MOVE GF@FuncReturn TF@strlen\n");
  printf("RETURN\n");
  printf("LABEL chrend\n");
}

// func readString() -> String?
void ReadString() {
  printf("JUMP readStringEnd\n");
  printf("LABEL readString\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");

    printf("DEFVAR LF@$ARG_LEN\n");
    printf("POPS LF@$ARG_LEN\n");

    printf("DEFVAR LF@ReadString\n");
  printf("READ LF@ReadString string\n");
  printf("POPFRAME\n");
  printf("MOVE GF@FuncReturn TF@ReadString\n");
  printf("RETURN\n");
  printf("LABEL readStringEnd\n");
}

// func readInt() -> Int?
void ReadInt() {
  printf("JUMP ReadIntEnd\n");
  printf("LABEL readInt\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  printf("DEFVAR LF@ReadInt\n");
  printf("READ LF@ReadInt int\n");
  printf("POPFRAME\n");
  printf("MOVE GF@FuncReturn TF@ReadInt\n");
  printf("RETURN\n");
  printf("LABEL ReadIntEnd\n");
}

// call ReadDouble
// func readDouble() -> Double?
void ReadDouble() {
  printf("JUMP readDoubleEnd\n");
  printf("LABEL readDouble\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  printf("DEFVAR LF@ReadFloat\n");
  printf("READ LF@ReadFloat float\n");
  printf("POPFRAME\n");
  printf("MOVE GF@FuncReturn TF@ReadFloat\n");
  printf("RETURN\n");
  printf("LABEL readDoubleEnd\n");
}

// func Int2Double(_ term ∶ Int) -> Double – Vrátí hodnotu celočíselného termu
// term konvertovanou na desetinné číslo. Pro konverzi z celého čísla využijte
// odpovídající instrukci z IFJcode23.
void Int2Double() {
  printf("JUMP Int2DoubleEnd\n");
  printf("LABEL Int2Double\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  printf("DEFVAR LF@tempInt\n");
  printf("POPS LF@tempInt\n");
  printf("INT2FLOAT LF@IntToFloat LF@tempInt\n");
  printf("POPFRAME\n");
  printf("MOVE GF@FuncReturn TF@IntToFloat\n");
  printf("RETURN\n");
  printf("LABEL Int2DoubleEnd\n");
}

// func Double2Int(_ term ∶ Double) -> Int – Vrátí hodnotu desetinného termu
// term konvertovanou na celé číslo, a to oříznutím desetinné části. Pro
// konverzi z desetinného čísla využijte odpovídající instrukci z IFJcode23.
void Double2Int() {
  printf("JUMP Double2IntEnd\n");
  printf("LABEL Double2Int\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  printf("DEFVAR LF@tempDouble\n");
  printf("POPS LF@tempDouble\n");
  printf("FLOAT2INT LF@FloatToInt LF@tempDouble\n");
  printf("POPFRAME\n");
  printf("MOVE GF@FuncReturn TF@IFloatToInt\n");
  printf("RETURN\n");
  printf("LABEL Double2IntEnd\n");
}

// func length(_ 𝑠 : String) -> Int – Vrátí délku (počet znaků) řetězce 𝑠. Např.
// length("x\nz") vrací 3.
void StrLength() {
  printf("JUMP lengthEnd\n");
  printf("LABEL length\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  printf("DEFVAR LF@tempString\n");
  printf("POPS LF@tempString\n");
  printf("STRLEN LF@StringLegnth LF@tempString\n");
  printf("POPFRAME\n");
  printf("MOVE GF@FuncReturn TF@StringLegnth\n");
  printf("RETURN\n");
  printf("LABEL lengthEnd\n");
}

// op1 = int to store
// res = register to store
void StoreInt(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("DEFVAR LF@r%d\n", get_reg_new(addressTable));
  printf("MOVE LF@r%d int@%lld\n", get_reg_cur(addressTable),
         grammarToken->tokensHolder[0]->data.integer_value);
  grammarToken->reg = get_reg_cur(addressTable);
  grammarToken->isGlobal = false;
}

void StoreDouble(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("DEFVAR LF@r%d\n", get_reg_new(addressTable));
  printf("MOVE LF@r%d float@%a\n", get_reg_cur(addressTable),
         grammarToken->tokensHolder[0]->data.double_value);
  grammarToken->reg = get_reg_cur(addressTable);
  grammarToken->isGlobal = false;
}

void StoreBrackets(GrammarToken *grammarToken, AddressTable *addressTable) {
    grammarToken->reg = grammarToken->tokensHolder[1]->data.grammarToken->reg;
    grammarToken->isGlobal = grammarToken->tokensHolder[1]->data.grammarToken->isGlobal;
}

void StoreBool(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("DEFVAR LF@r%d\n", get_reg_new(addressTable));
  if (grammarToken->tokensHolder[0]->data.integer_value) {
    printf("MOVE LF@r%d bool@true\n", get_reg_cur(addressTable));
  } else {
    printf("MOVE LF@r%d bool@false\n", get_reg_cur(addressTable));
  }
  grammarToken->reg = get_reg_cur(addressTable);
  grammarToken->isGlobal = false;
}

void StoreNil(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("DEFVAR LF@r%d\n", get_reg_new(addressTable));
  printf("MOVE LF@r%d nil@nil\n", get_reg_cur(addressTable));
  grammarToken->reg = get_reg_cur(addressTable);
  grammarToken->isGlobal = false;
}

// typedef struct string {
//   size_t length;
//   char *data;
// } String;
void StoreString(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("DEFVAR LF@r%d\n", get_reg_new(addressTable));
  //  if (grammarToken->tokensHolder[0]->data.string.length == 0) {
  //    printf("MOVE LF@r%d nil@nil\n", get_reg_cur(addressTable));//TODO wtf
  //    empty string
  //  } else {
  //    printf("MOVE LF@r%d string@\n",get_reg_cur(addressTable));
  //    printf("DEFVAR TF@temp\n");
  //    printf("DEFVAR TF@tempSymb\n");
  //    for (int i = 0; i < grammarToken->tokensHolder[0]->data.string.length;
  //    i++) {
  //      if (isalpha(grammarToken->tokensHolder[0]->data.string.data[i])) {
  //        printf("MOVE TF@temp string@%c\n",
  //        grammarToken->tokensHolder[0]->data.string.data[i]); printf("CONCAT
  //        LF@r%d LF@r%d
  //        TF@temp\n",get_reg_cur(addressTable),get_reg_cur(addressTable));
  //      } else {
  //        printf("MOVE TF@temp string@%c\n",
  //        grammarToken->tokensHolder[0]->data.string.data[i]);
  //        printf("STRI2INT TF@tempSymb TF@temp int@0\n");
  //        printf("CONCAT LF@r%d LF@r%d
  //        string@\\\n",get_reg_cur(addressTable),get_reg_cur(addressTable));
  //        printf("CONCAT LF@r%d LF@r%d
  //        TF@tempSymb\n",get_reg_cur(addressTable),get_reg_cur(addressTable));
  //      }
  //    }
  //  } GUYS WTF what this all means????
  printf("MOVE LF@r%d string@", get_reg_cur(addressTable));
  char *str = grammarToken->tokensHolder[0]->data.string.data;
  int sz = strlen(str);
  for (int i = 0; i < sz; i++) {
    printf("\\%03d", (int)str[i]);
  }
  printf("\n");
  grammarToken->reg = get_reg_cur(addressTable);
}

void OrInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n", res);
  printf("OR LF@r%d %s@r%d %s@r%d\n", res,
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
}

void AndInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n", res);
  printf("AND LF@r%d %s@r%d %s@r%d\n", res,
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void NotInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n", res);
  printf("NOT LF@r%d %s@r%d\n", res,
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

//{E, PLUS, E}
// E -> {F}
// GrammarToken -> {TOKEN, TOKEN, TOKEN, ...}
// TOKEN -> GrammarToken
void SumInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
    int res = get_reg_new(addressTable);
    if (grammarToken->returnType == STRING) {
    printf("DEFVAR LF@r%d\n", res);
    printf("CONCAT LF@r%d %s@r%d %s@r%d\n",
               res,
               registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
               grammarToken->tokensHolder[0]->data.grammarToken->reg,
               registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
               grammarToken->tokensHolder[2]->data.grammarToken->reg);
    }
    else {
      printf("DEFVAR LF@r%d\n", res);
      printf("ADD LF@r%d %s@r%d %s@r%d\n",
             res,
             registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
           grammarToken->tokensHolder[0]->data.grammarToken->reg,
             registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
           grammarToken->tokensHolder[2]->data.grammarToken->reg);
    }
    grammarToken->reg = get_reg_cur(addressTable);
    grammarToken->isGlobal = false;
  }

void SubInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n", res);
  printf("SUB LF@r%d %s@r%d %s@r%d\n", res,
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void MulInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  printf("DEFVAR LF@r%d\n", res);
  printf("MUL LF@r%d %s@r%d %s@r%d\n", res,
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void DivInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
//  printf("CREATEFRAME\n");
//  printf("PUSHFRAME\n");

  int firstE = get_reg_new(addressTable);
  int secondE = get_reg_new(addressTable);
  printf("DEFVAR LF@temp%d\n", firstE);
  printf("DEFVAR LF@temp%d\n", secondE);

   printf("INT2FLOAT LF@temp%d %s@r%d\n",
         firstE,
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg);

   printf("INT2FLOAT LF@temp%d %s@r%d\n",
          secondE,
          registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
          grammarToken->tokensHolder[2]->data.grammarToken->reg);

  printf("DEFVAR LF@r%d\n", res);
  printf("DIV LF@r%d LF@r%d LF@r%d\n", res,
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  //  printf("POPFRAME\n");
  grammarToken->reg = get_reg_cur(addressTable);
  grammarToken->isGlobal = false;
}

void EqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  //  printf("CREATEFRAME\n");
  //  printf("PUSHFRAME\n");
  printf("DEFVAR LF@r%d\n", res);
  printf("EQ LF@r%d %s@r%d %s@r%d\n", res,
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  //  printf("POPFRAME\n");
  grammarToken->reg = get_reg_cur(addressTable);
}

void NotEqualInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  //  printf("CREATEFRAME\n");
  //  printf("PUSHFRAME\n");
  printf("DEFVAR LF@r%d\n", res);
  printf("JUMPIFNEQ NotEqual %s@r%d %s@r%d\n",
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("MOVE LF@r%d bool@false\n", res);
  //  printf("POPFRAME\n");
  printf("JUMP NotEqualInterCodeEnd\n");

  printf("LABEL NotEqual\n");
  printf("MOVE LF@r%d bool@true\n", res);
  //  printf("POPFRAME\n");
  printf("LABEL NotEqualInterCodeEnd\n");
  grammarToken->reg = get_reg_cur(addressTable);
}

void GreaterInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  //  printf("CREATEFRAME\n");
  //  printf("PUSHFRAME\n");
  printf("DEFVAR LF@r%d\n", res);
  printf("GT LF@r%d %s@r%d %s@r%d\n", res,
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  //printf("POPFRAME\n");
  grammarToken->reg = get_reg_cur(addressTable);
}

void LessInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  //  printf("CREATEFRAME\n");
  //  printf("PUSHFRAME\n");
  printf("DEFVAR LF@r%d\n", res);
  printf("LT LF@r%d %s@r%d %s@r%d\n", res,
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  //  printf("POPFRAME\n");
  grammarToken->reg = get_reg_cur(addressTable);
}

void GreaterEqualInterCode(GrammarToken *grammarToken,
                           AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
//  printf("CREATEFRAME\n");
//  printf("PUSHFRAME\n");
  printf("DEFVAR LF@tempBool0\n");
  printf("GT LF@tempBool0 %s@r%d %s@r%d\n",
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("DEFVAR LF@tempBool1\n");
  printf("EQ LF@tempBool1 %s@r%d %s@r%d\n",
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("DEFVAR LF@r%d\n", res);
  printf("OR LF@r%d LF@tempBool0 LF@tempBool1\n", res);
//  printf("POPFRAME\n");
  grammarToken->reg = get_reg_cur(addressTable);
}

void LessEqualInterCode(GrammarToken *grammarToken,
                        AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  //printf("CREATEFRAME\n");
  //printf("PUSHFRAME\n");
  printf("DEFVAR LF@tempBool0\n");
  printf("LT LF@tempBool0 %s@r%d %s@r%d\n",
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("DEFVAR LF@tempBool1\n");
  printf("EQ TF@tempBool1 %s@r%d %s@r%d\n",
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg,
         registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[2]->data.grammarToken->reg);
  printf("DEFVAR LF@r%d\n", res);
  printf("OR LF@r%d LF@tempBool0 LF@tempBool1\n", res);
  //printf("POPFRAME\n");
  grammarToken->reg = get_reg_cur(addressTable);
}

void SoftUnwrapInterCode(GrammarToken *grammarToken,
                         AddressTable *addressTable) {
  int res = get_reg_new(addressTable);
  if (grammarToken->tokensHolder[0]->data.grammarToken->reg == -1) {
    printf("DEFVAR LF@r%d\n", res);
    printf("MOVE LF@r%d %s@r%d\n", res,
           registerPrefixGen(grammarToken->tokensHolder[2]->data.grammarToken->isGlobal),
           grammarToken->tokensHolder[2]->data.grammarToken->reg);
  }
  grammarToken->reg = get_reg_cur(addressTable);
}

void Write() {
  printf("JUMP EscapeWrite\n");
  printf("LABEL write\n");
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  printf("POPS GF@__ArgCount__\n");
  printf("JUMPIFEQ ReturnWrite GF@__ArgCount__ int@0\n"); // if argCount == 0
                                                          // jump label return
  printf("LABEL ForWrite\n");
  printf("SUB GF@__ArgCount__ GF@__ArgCount__ int@1\n");
  printf("POPS GF@__Arg__\n");
  printf("WRITE GF@__Arg__\n"); // write pop
  printf("JUMPIFNEQ ForWrite GF@__ArgCount__ int@0\n");
  printf("POPFRAME\n");

  // label return
  printf("LABEL ReturnWrite\n");
  printf("RETURN\n");
  printf("LABEL EscapeWrite\n");
}

void FuncInitialize(GrammarToken *grammarToken, AddressTable *addressTable) {
  init_function(addressTable, &grammarToken->tokensHolder[1]->data.string);
  printf("JUMP Escape%s\n", grammarToken->tokensHolder[1]->data.string.data);
  printf("LABEL %s\n", grammarToken->tokensHolder[1]->data.string.data);
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
  printf("DEFVAR LF@trash\n");
  printf("POPS LF@trash\n");
  if (grammarToken->tokensHolder[3]->data.grammarToken->tokensHolderSize != 0) {
    GrammarToken *curToken =
        grammarToken->tokensHolder[3]->data.grammarToken; // PARAMS
    bool isGlobal = false;
    int reg = AT_create(addressTable, &curToken->tokensHolder[0]
                                           ->data.grammarToken->tokensHolder[1]
                                           ->data.string, &isGlobal);
    if (reg == -1)
      exit(3);
    printf("DEFVAR %s@r%d\n", registerPrefixGen(isGlobal), reg); // ID NAME
    printf("POPS %s@r%d\n", registerPrefixGen(isGlobal), reg);
    curToken = curToken->tokensHolder[1]->data.grammarToken; // PARAMS_TMP

    while (curToken->tokensHolderSize != 0) {
      reg = AT_create(addressTable, &curToken->tokensHolder[1]
                                         ->data.grammarToken->tokensHolder[1]
                                         ->data.grammarToken->tokensHolder[1]
                                         ->data.string, &isGlobal);
      if (reg == -1)
        exit(3);
      printf("DEFVAR %s@r%d\n", registerPrefixGen(isGlobal),reg);
      printf("POPS %s@r%d\n", registerPrefixGen(isGlobal),reg);
      curToken = curToken->tokensHolder[1]->data.grammarToken;
    }
  }
}

void FuncInitializeEscape(GrammarToken *grammarToken,
                          AddressTable *addressTable) {
  printf("POPFRAME\n");
  printf("RETURN\n");
  printf("LABEL Escape%s\n", grammarToken->tokensHolder[1]->data.string.data);
  end_function(addressTable);
}

// POSTORDSADSD
// grammar_rule_create(F, NULL, NULL, NULL, (TokenType[]){ID, F_CALL}, 2),
void FuncCall(GrammarToken *grammarToken, AddressTable *addressTable) {
  if (grammarToken->tokensHolder[1]->data.grammarToken->tokensHolderSize == 0) {
    int reg = AT_get(addressTable, &grammarToken->tokensHolder[0]->data.string, &(grammarToken->isGlobal));
    grammarToken->reg = reg;
  } else {
    printf("CALL %s\n", grammarToken->tokensHolder[0]->data.string.data);
    int resReg = get_reg_new(addressTable);
    printf("DEFVAR LF@r%d\n", resReg);
    printf("MOVE LF@r%d GF@FuncReturn\n", resReg);
    grammarToken->reg = resReg;
    grammarToken->isGlobal = false;
  }
}

void FuncArgAdd(GrammarToken *grammarToken, AddressTable *addressTable) {
  int argCount = get_args(addressTable);//2
  int start = get_reg_cur(addressTable); //4

  for (int i = 0; i < argCount; i++) {
    printf("DEFVAR LF@tempArg%d\n", get_reg_new(addressTable)); //5, 6
    printf("POPS LF@tempArg%d\n", get_reg_cur(addressTable));
  }

  for (int i = start+1; i <= get_reg_cur(addressTable); i++) {
    printf("PUSHS LF@tempArg%d\n", i);
  }

  printf("MOVE GF@__ArgCount__ int@%d\n", argCount);
  printf("PUSHS GF@__ArgCount__\n");
}

void PushArg(GrammarToken *grammarToken, AddressTable *addressTable) {
  add_arg(addressTable);
  printf("PUSHS %s@r%d\n",
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg);
}

void PushArgLabeled(GrammarToken *grammarToken, AddressTable *addressTable) {
  add_arg(addressTable);
  printf("PUSHS %s@r%d\n",
         registerPrefixGen(grammarToken->tokensHolder[1]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[1]->data.grammarToken->reg);
}

// void HardUnwrapInterCode(GrammarToken *grammarToken, AddressTable
// *addressTable) {
//   if (addressCode->op1 == -1) {
//     printf("DEFVAR LF@r%d\n",addressCode->result);
//     printf("MOVE LF@r%d LF@r%d\n",addressCode->result,addressCode->op2);
//   }
// }

void HardUnwrapInterCode(GrammarToken *grammarToken,
                         AddressTable *addressTable) {
  // printf("DEFVAR LF@tempReg\n");
  // printf("MOVE LF@tempReg TF@r%d\n",
  // grammarToken->tokensHolder[0]->data.grammarToken->reg);
  printf("JUMPIFEQ ExitIfZero %s@r%d nil@nil\n",
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg);
  printf("JUMP EscapeHardUnwrap\n");
  printf("LABEL ExitIfZero\n");
  printf("EXIT int@57\n");
  printf("LABEL EscapeHardUnwrap\n");
}

void WhileInitInterCode(GrammarToken *grammarToken,
                        AddressTable *addressTable) {
  int num = init_cycle(addressTable);
  printf("LABEL cycle%d\n", num);
}

void CondInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("JUMPIFEQ BLOCK%d %s@r%d bool@true\n",
         get_cur_cycle(addressTable),
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg);
  printf("JUMPIFEQ ESCAPE%d %s@r%d bool@false\n", get_cur_cycle(addressTable),
         registerPrefixGen(grammarToken->tokensHolder[0]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[0]->data.grammarToken->reg);
  printf("LABEL BLOCK%d\n", get_cur_cycle(addressTable));
}

void BlockWhileInterCode(GrammarToken *grammarToken,
                         AddressTable *addressTable) {
  printf("JUMP cycle%d\n", get_cur_cycle(addressTable));
  printf("LABEL ESCAPE%d\n", get_cur_cycle(addressTable));
}

void BreakInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("JUMP ESCAPE%d\n", get_cur_cycle(addressTable));
}

void ContinueInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("JUMP cycle%d\n", get_cur_cycle(addressTable));
}

void ReturnInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("MOVE GF@ReturnFunc %s@r%d\n",
         registerPrefixGen(grammarToken->tokensHolder[1]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[1]->data.grammarToken->reg);
}

void PreOrderForIf(GrammarToken *grammarToken, AddressTable *addressTable) {
  init_cycle(addressTable);
}

void PreOrderForIfEslse(GrammarToken *grammarToken,
                        AddressTable *addressTable) {
  printf("JUMP EXITIF%d\n", get_cur_cycle(addressTable));
  printf("LABEL ESCAPE%d\n", get_cur_cycle(addressTable));
}

void PostOrderForIf(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("LABEL EXITIF%d\n", get_cur_cycle(addressTable));
  end_cycle(addressTable);
}

void VarIdInit(GrammarToken *grammarToken, AddressTable *addressTable) {
  int reg =
      AT_create(addressTable, &grammarToken->tokensHolder[0]->data.string, &grammarToken->isGlobal);
  if (reg == -1)
    exit(3);
  printf("DEFVAR %s@r%d\n", registerPrefixGen(grammarToken->isGlobal), reg);
  printf("MOVE %s@r%d LF@r%d\n", registerPrefixGen(grammarToken->isGlobal),
         reg, //GF@FuncReturn
         grammarToken->tokensHolder[1]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void VarTypedIdInit(GrammarToken *grammarToken, AddressTable *addressTable) {
  int reg =
      AT_create(addressTable, &grammarToken->tokensHolder[0]->data.string, &grammarToken->isGlobal);
  if (reg == -1)
    exit(3);
  printf("DEFVAR %s@r%d\n", registerPrefixGen(grammarToken->isGlobal), reg);
  printf("MOVE %s@r%d LF@r%d\n", registerPrefixGen(grammarToken->isGlobal),
         reg, //GF@FuncReturn
         grammarToken->tokensHolder[1]->data.grammarToken->reg);
  grammarToken->reg = get_reg_cur(addressTable);
}

void InitProcess(GrammarToken *grammarToken, AddressTable *addressTable) {
  grammarToken->reg = grammarToken->tokensHolder[1]->data.grammarToken->reg;
}

void IdAssignInterCode(GrammarToken *grammarToken, AddressTable *addressTable) {
  bool isGlobal = false;
  int reg = AT_get(addressTable, &(grammarToken->tokensHolder[0]->data.string), &isGlobal);
  printf("MOVE %s@r%d %s@r%d\n",
         registerPrefixGen(isGlobal),
         reg,
         registerPrefixGen(grammarToken->tokensHolder[1]->data.grammarToken->isGlobal),
         grammarToken->tokensHolder[1]->data.grammarToken->reg);
}

void StsCreateFrame(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("CREATEFRAME\n");
  printf("PUSHFRAME\n");
}

void StsPopFrame(GrammarToken *grammarToken, AddressTable *addressTable) {
  printf("POPFRAME\n");
}
// preorder function pro s ,which does init cycle
// preorder function for if else x2
// postorder function pro s, which ends cycle (?-and define lable for skip-?)