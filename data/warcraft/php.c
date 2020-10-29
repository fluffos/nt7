// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m虚空[2;37;0m[2;37;0m", ({"bool"}));        
        set("gender", "男性");                
        set("long", "暂无[2;37;0m
它是赵钱孙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "php");
        set("owner_name", "赵钱孙");
        set_temp("owner", "php");
        set_temp("owner_name", "赵钱孙");
        ::setup();
}
