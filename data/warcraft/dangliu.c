// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m鎏球[2;37;0m[2;37;0m", ({"bugliu"}));        
        set("gender", "男性");                
        set("long", "鎏球[2;37;0m
它是流行感冒的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "dangliu");
        set("owner_name", "流行感冒");
        set_temp("owner", "dangliu");
        set_temp("owner_name", "流行感冒");
        ::setup();
}
