// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"maaa"}));        
        set("gender", "女性");                
        set("long", "麒麟[2;37;0m
它是轩辕一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nba");
        set("owner_name", "轩辕一");
        set_temp("owner", "nba");
        set_temp("owner_name", "轩辕一");
        ::setup();
}
