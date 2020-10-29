// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[33m露[5m[33m露[2;37;0m[2;37;0m", ({"alu"}));        
        set("gender", "女性");                
        set("long", "只[2;37;0m
它是王启年的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "payaya");
        set("owner_name", "王启年");
        set_temp("owner", "payaya");
        set_temp("owner_name", "王启年");
        ::setup();
}
