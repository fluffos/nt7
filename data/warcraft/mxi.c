// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啾啾挤挤[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "mygift[2;37;0m
它是垃圾看见的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mxi");
        set("owner_name", "垃圾看见");
        set_temp("owner", "mxi");
        set_temp("owner_name", "垃圾看见");
        ::setup();
}
