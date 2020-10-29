// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("厅在[2;37;0m[2;37;0m", ({"hsdf"}));        
        set("gender", "男性");                
        set("long", "厅在[2;37;0m
它是二顶戴的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "huangf");
        set("owner_name", "二顶戴");
        set_temp("owner", "huangf");
        set_temp("owner_name", "二顶戴");
        ::setup();
}
