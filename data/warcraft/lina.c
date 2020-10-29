// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("神龙[2;37;0m[2;37;0m", ({"linag"}));        
        set("gender", "男性");                
        set("long", "神龙[2;37;0m
它是圣文的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lina");
        set("owner_name", "圣文");
        set_temp("owner", "lina");
        set_temp("owner_name", "圣文");
        ::setup();
}
