// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿娇[2;37;0m[2;37;0m", ({"bozi"}));        
        set("gender", "男性");                
        set("long", "阿娇[2;37;0m
它是莫非冤的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "spedmg");
        set("owner_name", "莫非冤");
        set_temp("owner", "spedmg");
        set_temp("owner_name", "莫非冤");
        ::setup();
}
