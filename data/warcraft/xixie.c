// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("诶飞翔[2;37;0m[2;37;0m", ({"xixieee"}));        
        set("gender", "女性");                
        set("long", "自由的飞翔[2;37;0m
它是习诶的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xixie");
        set("owner_name", "习诶");
        set_temp("owner", "xixie");
        set_temp("owner_name", "习诶");
        ::setup();
}
