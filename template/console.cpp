// mygpp is what the judge uses
alias mygpp="g++ -std=gnu++20 -x c++ -Wall -O2 -static -pipe -o $1 \"$1.cpp\" -lm"

alias comp="g++ -std=gnu++20 -O2 -Wall -Wextra -Wshadow -Wconversion"
alias dbg="comp -g -fsanitize=address,undefined -D_GLIBCXX_DEBUG"
// use    comp main.cpp && ./a.out    < "1.in" | diff "1.out" -
