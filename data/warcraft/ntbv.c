// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是爱田由的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ntbv");
        set("owner_name", "爱田由");
        set_temp("owner", "ntbv");
        set_temp("owner_name", "爱田由");
        ::setup();
}
