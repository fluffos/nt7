// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪宝贝[2;37;0m[2;37;0m", ({"hip"}));        
        set("gender", "女性");                
        set("long", "我的宝贝[2;37;0m
它是猪太郎的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "pig");
        set("owner_name", "猪太郎");
        set_temp("owner", "pig");
        set_temp("owner_name", "猪太郎");
        ::setup();
}
