// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("上官萧青[2;37;0m[2;37;0m", ({"cors"}));        
        set("gender", "女性");                
        set("long", "曾大战王者大陆中最顶级的四位高手，最终寡不敌众陨落在上官府中[2;37;0m
它是上官萧战的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "corw");
        set("owner_name", "上官萧战");
        set_temp("owner", "corw");
        set_temp("owner_name", "上官萧战");
        ::setup();
}
