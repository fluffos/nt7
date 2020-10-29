// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"ddddd"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是何兰兰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lanxxx");
        set("owner_name", "何兰兰");
        set_temp("owner", "lanxxx");
        set_temp("owner_name", "何兰兰");
        ::setup();
}
