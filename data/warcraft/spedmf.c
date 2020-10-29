// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("阿娇[2;37;0m[2;37;0m", ({"bozi"}));        
        set("gender", "男性");                
        set("long", "阿娇[2;37;0m
它是邓玉平的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "spedmf");
        set("owner_name", "邓玉平");
        set_temp("owner", "spedmf");
        set_temp("owner_name", "邓玉平");
        ::setup();
}
