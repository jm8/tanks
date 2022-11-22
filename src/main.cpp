#include "FEHLCD.h"

int main() {
    while (1) {
        LCD.Clear(0xff0000);
        LCD.WriteLine("Hello world");
        LCD.Update();
        // Never end
    }
    return 0;
}
