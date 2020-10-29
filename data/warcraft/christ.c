// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无心[2;37;0m[2;37;0m", ({"togo"}));        
        set("gender", "女性");                
        set("long", "no[2;37;0m
它是高恬的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "christ");
        set("owner_name", "高恬");
        set_temp("owner", "christ");
        set_temp("owner_name", "高恬");
        ::setup();
}
