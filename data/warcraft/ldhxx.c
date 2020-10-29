// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小王八蛋[2;37;0m[2;37;0m", ({"kidkid"}));        
        set("gender", "男性");                
        set("long", "小王八蛋[2;37;0m
它是林欣羽的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ldhxx");
        set("owner_name", "林欣羽");
        set_temp("owner", "ldhxx");
        set_temp("owner_name", "林欣羽");
        ::setup();
}
