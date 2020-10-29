// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m灭绝师太[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "女性");                
        set("long", "灭绝师太[2;37;0m
它是见情的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "oooo");
        set("owner_name", "见情");
        set_temp("owner", "oooo");
        set_temp("owner_name", "见情");
        ::setup();
}
