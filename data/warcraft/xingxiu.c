// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"mmm"}));        
        set("gender", "男性");                
        set("long", "传说中的火焰鸟[2;37;0m
它是行修的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xingxiu");
        set("owner_name", "行修");
        set_temp("owner", "xingxiu");
        set_temp("owner_name", "行修");
        ::setup();
}
