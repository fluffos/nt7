// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("啾啾挤挤[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "啾啾挤挤[2;37;0m
它是沐艺的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "woodyi");
        set("owner_name", "沐艺");
        set_temp("owner", "woodyi");
        set_temp("owner_name", "沐艺");
        ::setup();
}
