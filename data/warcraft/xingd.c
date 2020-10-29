// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星云[2;37;0m[2;37;0m", ({"xingda"}));        
        set("gender", "男性");                
        set("long", "星云[2;37;0m
它是星云二的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xingd");
        set("owner_name", "星云二");
        set_temp("owner", "xingd");
        set_temp("owner_name", "星云二");
        ::setup();
}
