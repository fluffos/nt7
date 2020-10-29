// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啾啾挤挤[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "更好非结构化[2;37;0m
它是打桩荡荡的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mxv");
        set("owner_name", "打桩荡荡");
        set_temp("owner", "mxv");
        set_temp("owner_name", "打桩荡荡");
        ::setup();
}
