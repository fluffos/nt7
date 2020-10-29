// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蓑衣[2;37;0m[2;37;0m", ({"suo"}));        
        set("gender", "女性");                
        set("long", "蓑衣[2;37;0m
它是浮厝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cuo");
        set("owner_name", "浮厝");
        set_temp("owner", "cuo");
        set_temp("owner_name", "浮厝");
        ::setup();
}
