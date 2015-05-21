cls
win_flex example1.l
win_bison -d --debug --verbose example1.y
g++ -o parser2 lex.yy.c example1.tab.c -w

parser2 < input.txt