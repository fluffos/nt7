// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麻雀[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "男性");                
        set("long", "麻雀[2;37;0m
它是幽剑的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yuyuxx");
        set("owner_name", "幽剑");
        set_temp("owner", "yuyuxx");
        set_temp("owner_name", "幽剑");
        ::setup();
}
