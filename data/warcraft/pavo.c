// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m孔雀[2;37;0m[2;37;0m", ({"kongque"}));        
        set("gender", "女性");                
        set("long", "孔雀开屏[2;37;0m
它是翩翩婉儿的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "pavo");
        set("owner_name", "翩翩婉儿");
        set_temp("owner", "pavo");
        set_temp("owner_name", "翩翩婉儿");
        ::setup();
}
