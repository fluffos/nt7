// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("羽毛[2;37;0m[2;37;0m", ({"yuant"}));        
        set("gender", "男性");                
        set("long", "撒[2;37;0m
它是清羽的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jsatg");
        set("owner_name", "清羽");
        set_temp("owner", "jsatg");
        set_temp("owner_name", "清羽");
        ::setup();
}
