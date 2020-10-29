// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m[5m火鸡[2;37;0m[2;37;0m", ({"bigbird"}));        
        set("gender", "男性");                
        set("long", "大大的一只火鸡。[2;37;0m
它是武大狼的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "noone");
        set("owner_name", "武大狼");
        set_temp("owner", "noone");
        set_temp("owner_name", "武大狼");
        ::setup();
}
