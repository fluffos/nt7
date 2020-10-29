// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"mycar"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是楚北雨的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zbdy");
        set("owner_name", "楚北雨");
        set_temp("owner", "zbdy");
        set_temp("owner_name", "楚北雨");
        ::setup();
}
