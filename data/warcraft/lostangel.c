// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("塞斯[2;37;0m[2;37;0m", ({"sess"}));        
        set("gender", "男性");                
        set("long", "天使[2;37;0m
它是天使之城的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lostangel");
        set("owner_name", "天使之城");
        set_temp("owner", "lostangel");
        set_temp("owner_name", "天使之城");
        ::setup();
}
