// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星野[2;37;0m[2;37;0m", ({"yunxin"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是独孤毒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "duman");
        set("owner_name", "独孤毒");
        set_temp("owner", "duman");
        set_temp("owner_name", "独孤毒");
        ::setup();
}
