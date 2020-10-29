// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("旧主人[2;37;0m[2;37;0m", ({"xinlong"}));        
        set("gender", "男性");                
        set("long", "我日[2;37;0m
它是新阶级的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xin");
        set("owner_name", "新阶级");
        set_temp("owner", "xin");
        set_temp("owner_name", "新阶级");
        ::setup();
}
