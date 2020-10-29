// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啾啾挤挤[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "mygift[2;37;0m
它是原来厉害的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mxm");
        set("owner_name", "原来厉害");
        set_temp("owner", "mxm");
        set_temp("owner_name", "原来厉害");
        ::setup();
}
