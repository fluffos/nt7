// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("柏芝[2;37;0m[2;37;0m", ({"bozi"}));        
        set("gender", "男性");                
        set("long", "柏芝[2;37;0m
它是白愁飞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tntntk");
        set("owner_name", "白愁飞");
        set_temp("owner", "tntntk");
        set_temp("owner_name", "白愁飞");
        ::setup();
}
