// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m仙鹤[2;37;0m[2;37;0m", ({"car"}));        
        set("gender", "男性");                
        set("long", "mygift[2;37;0m
它是华佗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tuo");
        set("owner_name", "华佗");
        set_temp("owner", "tuo");
        set_temp("owner_name", "华佗");
        ::setup();
}
