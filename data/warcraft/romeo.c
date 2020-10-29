// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m宝马[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "this is bmw[2;37;0m
它是马马的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "romeo");
        set("owner_name", "马马");
        set_temp("owner", "romeo");
        set_temp("owner_name", "马马");
        ::setup();
}
