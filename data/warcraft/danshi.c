// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小雪[2;37;0m[2;37;0m", ({"mud"}));        
        set("gender", "女性");                
        set("long", "多云[2;37;0m
它是炼丹师的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "danshi");
        set("owner_name", "炼丹师");
        set_temp("owner", "danshi");
        set_temp("owner_name", "炼丹师");
        ::setup();
}
