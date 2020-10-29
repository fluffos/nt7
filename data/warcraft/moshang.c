// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m麒麟[2;37;0m[2;37;0m", ({"qianhui"}));        
        set("gender", "男性");                
        set("long", "好吃懒做[2;37;0m
它是陌上千回的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "moshang");
        set("owner_name", "陌上千回");
        set_temp("owner", "moshang");
        set_temp("owner_name", "陌上千回");
        ::setup();
}
