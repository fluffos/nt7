// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是留一手的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "handa");
        set("owner_name", "留一手");
        set_temp("owner", "handa");
        set_temp("owner_name", "留一手");
        ::setup();
}
