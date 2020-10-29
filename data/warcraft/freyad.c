// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("圆[2;37;0m[2;37;0m", ({"dragonii"}));        
        set("gender", "男性");                
        set("long", "圆[2;37;0m
它是思仁的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "freyad");
        set("owner_name", "思仁");
        set_temp("owner", "freyad");
        set_temp("owner_name", "思仁");
        ::setup();
}
