// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m魔像飞[2;37;0m[2;37;0m", ({"feitian"}));        
        set("gender", "男性");                
        set("long", "飞天魔像[2;37;0m
它是钝剑的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dunjian");
        set("owner_name", "钝剑");
        set_temp("owner", "dunjian");
        set_temp("owner_name", "钝剑");
        ::setup();
}
