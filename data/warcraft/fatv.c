// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽似[2;37;0m[2;37;0m", ({"aav"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是加药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatv");
        set("owner_name", "加药");
        set_temp("owner", "fatv");
        set_temp("owner_name", "加药");
        ::setup();
}
