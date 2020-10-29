// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽拔[2;37;0m[2;37;0m", ({"aaz"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是菹药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatz");
        set("owner_name", "菹药");
        set_temp("owner", "fatz");
        set_temp("owner_name", "菹药");
        ::setup();
}
