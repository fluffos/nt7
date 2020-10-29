// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "猪[2;37;0m
它是土西游的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "txy");
        set("owner_name", "土西游");
        set_temp("owner", "txy");
        set_temp("owner_name", "土西游");
        ::setup();
}
