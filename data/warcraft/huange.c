// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("要于[2;37;0m[2;37;0m", ({"hdfsg"}));        
        set("gender", "男性");                
        set("long", "要于[2;37;0m
它是花样夺的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huange");
        set("owner_name", "花样夺");
        set_temp("owner", "huange");
        set_temp("owner_name", "花样夺");
        ::setup();
}
