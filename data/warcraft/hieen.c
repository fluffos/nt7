// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("死龙[2;37;0m[2;37;0m", ({"hid"}));        
        set("gender", "男性");                
        set("long", "死龙[2;37;0m
它是杀柏的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hieen");
        set("owner_name", "杀柏");
        set_temp("owner", "hieen");
        set_temp("owner_name", "杀柏");
        ::setup();
}
