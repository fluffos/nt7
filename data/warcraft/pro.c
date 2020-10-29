// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m梦想天空[2;37;0m[2;37;0m", ({"int"}));        
        set("gender", "男性");                
        set("long", "无[2;37;0m
它是修炼者的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "pro");
        set("owner_name", "修炼者");
        set_temp("owner", "pro");
        set_temp("owner_name", "修炼者");
        ::setup();
}
