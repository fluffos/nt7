// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m龙宝宝[2;37;0m[2;37;0m", ({"longbaobao"}));        
        set("gender", "男性");                
        set("long", "一只肥肥的龙宝宝[2;37;0m
它是独孤一笑的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dgyx");
        set("owner_name", "独孤一笑");
        set_temp("owner", "dgyx");
        set_temp("owner_name", "独孤一笑");
        ::setup();
}
