// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m一小月份[2;37;0m[2;37;0m", ({"jana"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是一月的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "jan");
        set("owner_name", "一月");
        set_temp("owner", "jan");
        set_temp("owner_name", "一月");
        ::setup();
}
