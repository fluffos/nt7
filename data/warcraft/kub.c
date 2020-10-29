// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("矿龙的[2;37;0m[2;37;0m", ({"huanlong"}));        
        set("gender", "男性");                
        set("long", "矿龙的[2;37;0m
它是衣服的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kub");
        set("owner_name", "衣服");
        set_temp("owner", "kub");
        set_temp("owner_name", "衣服");
        ::setup();
}
