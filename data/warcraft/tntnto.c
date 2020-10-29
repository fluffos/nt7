// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("柏芝[2;37;0m[2;37;0m", ({"bozi"}));        
        set("gender", "男性");                
        set("long", "柏芝[2;37;0m
它是李沉粥的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tntnto");
        set("owner_name", "李沉粥");
        set_temp("owner", "tntnto");
        set_temp("owner_name", "李沉粥");
        ::setup();
}
