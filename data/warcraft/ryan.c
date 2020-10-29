// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m小龙女[2;37;0m[2;37;0m", ({"baby"}));        
        set("gender", "女性");                
        set("long", "小龙女[2;37;0m
它是独孤宇的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ryan");
        set("owner_name", "独孤宇");
        set_temp("owner", "ryan");
        set_temp("owner_name", "独孤宇");
        ::setup();
}
