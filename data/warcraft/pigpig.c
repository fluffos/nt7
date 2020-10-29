// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m宾利[2;37;0m[2;37;0m", ({"pigpiga"}));        
        set("gender", "男性");                
        set("long", "宾利牌小轿车[2;37;0m
它是猪猪公子的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pigpig");
        set("owner_name", "猪猪公子");
        set_temp("owner", "pigpig");
        set_temp("owner_name", "猪猪公子");
        ::setup();
}
