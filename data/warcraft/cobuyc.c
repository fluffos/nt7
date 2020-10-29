// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("一只大鸟[2;37;0m[2;37;0m", ({"cobuycc"}));        
        set("gender", "男性");                
        set("long", "一只大鸟[2;37;0m
它是彩色的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cobuyc");
        set("owner_name", "彩色");
        set_temp("owner", "cobuyc");
        set_temp("owner_name", "彩色");
        ::setup();
}
