// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m百事可乐[2;37;0m[2;37;0m", ({"pesig"}));        
        set("gender", "男性");                
        set("long", "百事可乐[2;37;0m
它是阿尔九的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "aliversi");
        set("owner_name", "阿尔九");
        set_temp("owner", "aliversi");
        set_temp("owner_name", "阿尔九");
        ::setup();
}
