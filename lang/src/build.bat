cls
@rem --noline --c++ 
win_flex.exe --wincompat --outfile=lang.lex.yy.cpp lang.l
win_bison.exe lang.y -d --defines=lang.tab.h --output=lang.tab.cpp
