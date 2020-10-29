// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m百事可乐[2;37;0m[2;37;0m", ({"pepsi"}));        
        set("gender", "男性");                
        set("long", "百事可乐[2;37;0m
它是逍天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaotian");
        set("owner_name", "逍天");
        set_temp("owner", "xiaotian");
        set_temp("owner_name", "逍天");
        ::setup();
}
