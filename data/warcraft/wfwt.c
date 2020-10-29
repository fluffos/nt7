// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m飞[1;32m翔[1;36m九[1;32m州[2;37;0m[2;37;0m", ({"feiyang"}));        
        set("gender", "男性");                
        set("long", "条[2;37;0m
它是无法无天的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wfwt");
        set("owner_name", "无法无天");
        set_temp("owner", "wfwt");
        set_temp("owner_name", "无法无天");
        ::setup();
}
