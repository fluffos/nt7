// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("玩具麒麟[2;37;0m[2;37;0m", ({"weekendride"}));        
        set("gender", "男性");                
        set("long", "玩具麒麟[2;37;0m
它是周仲通的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "weekend");
        set("owner_name", "周仲通");
        set_temp("owner", "weekend");
        set_temp("owner_name", "周仲通");
        ::setup();
}
