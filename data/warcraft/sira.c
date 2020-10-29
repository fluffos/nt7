// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("龙[2;37;0m[2;37;0m", ({"aris"}));        
        set("gender", "男性");                
        set("long", "按时地方[2;37;0m
它是赵瑟的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sira");
        set("owner_name", "赵瑟");
        set_temp("owner", "sira");
        set_temp("owner_name", "赵瑟");
        ::setup();
}
