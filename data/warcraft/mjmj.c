// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "青龙[2;37;0m
它是张无羁的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "mjmj");
        set("owner_name", "张无羁");
        set_temp("owner", "mjmj");
        set_temp("owner_name", "张无羁");
        ::setup();
}
