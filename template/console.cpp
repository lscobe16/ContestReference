// mygpp is what the judge uses
alias mygpp="g++ -std=gnu++20 -x c++ -Wall -O2 -static -pipe -o $1 \"$1.cpp\" -lm"

alias comp="g++ -std=gnu++20 -O2 -Wall -Wextra -Wshadow -Wconversion"
alias dbg="comp -g -fsanitize=address,undefined"
// use    comp main.cpp && ./a.out
