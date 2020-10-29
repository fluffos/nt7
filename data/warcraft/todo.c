// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("云影[2;37;0m[2;37;0m", ({"yunyin"}));        
        set("gender", "男性");                
        set("long", "无以名之[2;37;0m
它是独孤问剑的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "todo");
        set("owner_name", "独孤问剑");
        set_temp("owner", "todo");
        set_temp("owner_name", "独孤问剑");
        ::setup();
}
