// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"noneys"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是钱不通的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "noneye");
        set("owner_name", "钱不通");
        set_temp("owner", "noneye");
        set_temp("owner_name", "钱不通");
        ::setup();
}
