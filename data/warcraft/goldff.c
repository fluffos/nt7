// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蛇[2;37;0m[2;37;0m", ({"goldfff"}));        
        set("gender", "男性");                
        set("long", "蛇[2;37;0m
它是金蛇的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "goldff");
        set("owner_name", "金蛇");
        set_temp("owner", "goldff");
        set_temp("owner_name", "金蛇");
        ::setup();
}
