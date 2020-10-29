// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m五步蛇[2;37;0m[2;37;0m", ({"nodd"}));        
        set("gender", "男性");                
        set("long", "七彩斑斓的小蛇，看起来天下无敌。[2;37;0m
它是赤宵的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "nod");
        set("owner_name", "赤宵");
        set_temp("owner", "nod");
        set_temp("owner_name", "赤宵");
        ::setup();
}
