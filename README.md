# SimpleLanguageParser GUI 
Implementation of GUI for [SimleLanguageParser project](https://github.com/Childcity/SimpleLanguageParser)

## Algorithm of this parser
&emsp;**Input Text**&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;*(written with my own syntax)*

       |
      \|
**Lexical Analyzer**&emsp;&emsp;&emsp;&emsp;&emsp;*(devide text on `lexems` and check all allowed symbols)*

      |
     \|
**List of Lexems**&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;*( `intermediate` representation of input lexems as json list)*

      |
     \|
**Syntactic Analyzer**&emsp;&emsp;&emsp;&emsp;*(check on valid syntax and build `AST tree` as result)*

      |
     \| 
&emsp;&emsp;**AST Tree**&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;*( `intermediate` representation of input program)*\
   
      |
     \|
&emsp;&emsp;**Reverse**\
**Polish Notation**&emsp;&emsp;&emsp;&emsp;&emsp;*(well, no comments)*\
&emsp;**and Executing**

## Screenshots of running program you can see below:

### When Lexical Analyzer and Syntactic Analyzer parsed without errors and input program executed (in Console)
![without_errors](/ScreenShots/все_ок_с_выводом.png)
![without_errors](/ScreenShots/все_ок_табл_лексем.png)

### When Lexical Analyzer found "unexpected token '&'" in line 1
![lex_error](/ScreenShots/ошибка_непредвид_токен.png)

### When Syntactic Analyzer found "undeclared token 'writ' "
![syn_error](/ScreenShots/ошибка_необьяв_идентиф.png)


### When Syntactic Analyzer found "undeclared token 'sumi' "
![syn_error](/ScreenShots/ошибка_необ_идентиф.png)


### AST tree of all program after success syntactic analyze
[ASTree realization](https://github.com/Childcity/ASTree/)
![ast_tree](/ScreenShots/ситакс_дерево.png)
