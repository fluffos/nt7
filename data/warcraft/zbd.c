// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞车[2;37;0m[2;37;0m", ({"mycar"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是楚北风的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zbd");
        set("owner_name", "楚北风");
        set_temp("owner", "zbd");
        set_temp("owner_name", "楚北风");
        ::setup();
}
