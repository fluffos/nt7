// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("柏芝[2;37;0m[2;37;0m", ({"bozi"}));        
        set("gender", "男性");                
        set("long", "柏芝[2;37;0m
它是天权子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xmdmd");
        set("owner_name", "天权子");
        set_temp("owner", "xmdmd");
        set_temp("owner_name", "天权子");
        ::setup();
}
