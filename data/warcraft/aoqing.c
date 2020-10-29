// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m疯虎[2;37;0m[2;37;0m", ({"fenghu"}));        
        set("gender", "男性");                
        set("long", "这是一只目露凶光的巨虎，十分骇人。[2;37;0m
它是敖青的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "aoqing");
        set("owner_name", "敖青");
        set_temp("owner", "aoqing");
        set_temp("owner_name", "敖青");
        ::setup();
}
