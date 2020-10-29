// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m麟麟[2;37;0m[2;37;0m", ({"qlql"}));        
        set("gender", "男性");                
        set("long", "和尚[2;37;0m
它是三千的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wdn");
        set("owner_name", "三千");
        set_temp("owner", "wdn");
        set_temp("owner_name", "三千");
        ::setup();
}
