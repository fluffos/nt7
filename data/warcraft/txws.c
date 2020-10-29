// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白玉小虎[2;37;0m[2;37;0m", ({"bhnv"}));        
        set("gender", "男性");                
        set("long", "一只大老虎.[2;37;0m
它是一阳神指的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "txws");
        set("owner_name", "一阳神指");
        set_temp("owner", "txws");
        set_temp("owner_name", "一阳神指");
        ::setup();
}
