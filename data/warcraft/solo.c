// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m空军一号[2;37;0m[2;37;0m", ({"johnny"}));        
        set("gender", "男性");                
        set("long", "我要坐空军一号[2;37;0m
它是司马甄寰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "solo");
        set("owner_name", "司马甄寰");
        set_temp("owner", "solo");
        set_temp("owner_name", "司马甄寰");
        ::setup();
}
