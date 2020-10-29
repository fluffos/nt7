// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("自行车[2;37;0m[2;37;0m", ({"sdfsa"}));        
        set("gender", "男性");                
        set("long", "自行车[2;37;0m
它是赫连天成的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bagbagd");
        set("owner_name", "赫连天成");
        set_temp("owner", "bagbagd");
        set_temp("owner_name", "赫连天成");
        ::setup();
}
