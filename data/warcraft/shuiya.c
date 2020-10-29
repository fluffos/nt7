// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小心[2;37;0m[2;37;0m", ({"xxxx"}));        
        set("gender", "男性");                
        set("long", "小心[2;37;0m
它是谁呀的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "shuiya");
        set("owner_name", "谁呀");
        set_temp("owner", "shuiya");
        set_temp("owner_name", "谁呀");
        ::setup();
}
