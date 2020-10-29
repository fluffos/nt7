// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("波多结衣顾子[2;37;0m[2;37;0m", ({"plgop"}));        
        set("gender", "男性");                
        set("long", "@miaoshu[2;37;0m
它是捣药四的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "ymgd");
        set("owner_name", "捣药四");
        set_temp("owner", "ymgd");
        set_temp("owner_name", "捣药四");
        ::setup();
}
