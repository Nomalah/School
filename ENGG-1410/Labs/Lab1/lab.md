I installed gcc and vscode and then opened a file named ex.c and wrote this:
```cpp
#include <stdio.h>

int main(void) {
    printf("Hello World!\n");
    return 0;
}
```
I used this command to compile it
```bash
gcc ex.c -o out.exe
# and ran it as such:
./out.exe
```

I then tried a whole bunch of different flags
```bash
gcc ex.c -O3 -Wall -Werror -o out.exe
# and ran it as such:
./out.exe
```
