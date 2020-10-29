// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙魔幻兽[2;37;0m[2;37;0m", ({"fffff"}));        
        set("gender", "男性");                
        set("long", "青龙魔幻兽[2;37;0m
它是不自由的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fea");
        set("owner_name", "不自由");
        set_temp("owner", "fea");
        set_temp("owner_name", "不自由");
        ::setup();
}
