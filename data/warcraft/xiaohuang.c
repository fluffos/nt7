// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("怡宝[2;37;0m[2;37;0m", ({"bao"}));        
        set("gender", "男性");                
        set("long", "怡宝[2;37;0m
它是逍黄的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaohuang");
        set("owner_name", "逍黄");
        set_temp("owner", "xiaohuang");
        set_temp("owner_name", "逍黄");
        ::setup();
}
