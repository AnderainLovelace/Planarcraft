#include "classes/PlanarcraftApplication.h"

int main(int argc, char * argv[]) {
    try {
        PlanarcraftApplication app(320, 240, 16, "Planarcraft");
        app.go();
    }
    catch (kuro::CException e) {
        puts(e.getMessage());
        return 1;
    }
    catch (...) {
        puts("Unknown Error");
        return 1;
    }
    return 0;
}