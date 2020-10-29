// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啾啾挤挤[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "更好非结构化[2;37;0m
它是改成嘛的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mxt");
        set("owner_name", "改成嘛");
        set_temp("owner", "mxt");
        set_temp("owner_name", "改成嘛");
        ::setup();
}
