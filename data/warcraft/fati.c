// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽一[2;37;0m[2;37;0m", ({"aai"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是首药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fati");
        set("owner_name", "首药");
        set_temp("owner", "fati");
        set_temp("owner_name", "首药");
        ::setup();
}
