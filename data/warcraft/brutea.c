// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("布布[2;37;0m[2;37;0m", ({"bruta"}));        
        set("gender", "男性");                
        set("long", "布布[2;37;0m
它是布一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "brutea");
        set("owner_name", "布一");
        set_temp("owner", "brutea");
        set_temp("owner_name", "布一");
        ::setup();
}
