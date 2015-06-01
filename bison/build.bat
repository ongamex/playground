cls
win_flex.exe --wincompat --header-file=lexer.h --outfile=lexer.cpp example1.l
win_bison.exe example1.y -d --defines=parser.h --output=parser.cpp --feature=all
g++ -o parser parser.cpp lexer.cpp main.cpp -w -fpermissive
