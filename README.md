
#1 Toy Compiler

#3 build步驟

編譯 flex 檔案
```shell=
flex flex.l
```

編譯 bison 檔案，其中下 -d 參數會產生標頭檔(預設檔名 yacc.tab.h)
```shell=
bison -d yacc.y
```

編譯所有檔案，產生執行檔，此即為編譯器(預設檔名 a.out)
```shell=
gcc main.c lex.yy.c lex.yy.h yacc.tab.c yacc.tab.h globals.h util.c util.h 
parse.h symtable.c symtable.h analyze.c analyze.h code_gen.c code_gen.h
```

執行編譯 Vanilla-c 測試檔案，產生一份 LLVM IR 檔案(.ll)
```shell=
./a.out test_file
```

用 LLVM 直譯器執行被編譯產生的 .ll 檔，在終端機顯示執行結果
```shell=
lli IR_Code.ll
```

將 .ll 格式轉換成特定架構的 assembly code(.s)
```shell=
llc IR_Code.ll
```

## 補充
直接用 clang 編譯一般的 .c 檔，同樣產生 .ll 檔
```shell=
clang -S -emit-llvm file.c
```

#Toy-Compiler
