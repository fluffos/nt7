// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("精工[2;37;0m[2;37;0m", ({"clothalong"}));        
        set("gender", "男性");                
        set("long", "喔唷[2;37;0m
它是缘分青衣的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "clotha");
        set("owner_name", "缘分青衣");
        set_temp("owner", "clotha");
        set_temp("owner_name", "缘分青衣");
        ::setup();
}
