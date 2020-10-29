// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("五号[2;37;0m[2;37;0m", ({"cafe"}));        
        set("gender", "男性");                
        set("long", "五号[2;37;0m
它是咖啡五号的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "limcafe");
        set("owner_name", "咖啡五号");
        set_temp("owner", "limcafe");
        set_temp("owner_name", "咖啡五号");
        ::setup();
}
