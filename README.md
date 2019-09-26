# SimpleLanguageParser GUI 
Implementation of GUI for [SimleLanguageParser project](https://github.com/Childcity/SimpleLanguageParser)

## Algorithm of this parser
  **Input Text**            *(written with my own syntax)*
      |
     \|
**Lexical Analyzer**      *(devide text on* **lexems** *and check all allowed symbols)*
      |
     \|
**List of Lexems**        *(* **intermediate** *representation of input lexems as json list)*
      |
     \|
**Syntactic Analyzer**    *(check on valid syntax and build AST tree as result)*
      |
     \| 
   **AST Tree**           *(* **intermediate** *representation of input program)*
      |
     \|
   **Reverse**
**Polish Notation**       *(well, no comments)*
 **and Executing**

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
