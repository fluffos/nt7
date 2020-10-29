// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("柏芝[2;37;0m[2;37;0m", ({"bozi"}));        
        set("gender", "男性");                
        set("long", "柏芝[2;37;0m
它是鬼八仙的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tntnti");
        set("owner_name", "鬼八仙");
        set_temp("owner", "tntnti");
        set_temp("owner_name", "鬼八仙");
        ::setup();
}
