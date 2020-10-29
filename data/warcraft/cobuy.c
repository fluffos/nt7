// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("七彩[2;37;0m[2;37;0m", ({"qicai"}));        
        set("gender", "女性");                
        set("long", "七彩色的颜色[2;37;0m
它是颜色的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "cobuy");
        set("owner_name", "颜色");
        set_temp("owner", "cobuy");
        set_temp("owner_name", "颜色");
        ::setup();
}
