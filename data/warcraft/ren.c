// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("菊花拿来[2;37;0m[2;37;0m", ({"mypet"}));        
        set("gender", "女性");                
        set("long", "菊花拿来[2;37;0m
它是菊花信的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ren");
        set("owner_name", "菊花信");
        set_temp("owner", "ren");
        set_temp("owner_name", "菊花信");
        ::setup();
}
