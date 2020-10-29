// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽柳[2;37;0m[2;37;0m", ({"aax"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是船药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatx");
        set("owner_name", "船药");
        set_temp("owner", "fatx");
        set_temp("owner_name", "船药");
        ::setup();
}
