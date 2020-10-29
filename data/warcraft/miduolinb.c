// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("米多淋麒麟[2;37;0m[2;37;0m", ({"miduolinride"}));        
        set("gender", "男性");                
        set("long", "米多淋麒麟[2;37;0m
它是米多二的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "miduolinb");
        set("owner_name", "米多二");
        set_temp("owner", "miduolinb");
        set_temp("owner_name", "米多二");
        ::setup();
}
