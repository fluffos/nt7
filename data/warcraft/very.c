// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("口袋[2;37;0m[2;37;0m", ({"mygift"}));        
        set("gender", "女性");                
        set("long", "口袋[2;37;0m
它是莫离去的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "very");
        set("owner_name", "莫离去");
        set_temp("owner", "very");
        set_temp("owner_name", "莫离去");
        ::setup();
}
