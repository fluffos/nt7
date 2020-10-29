// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("契约[2;37;0m[2;37;0m", ({"baifeng"}));        
        set("gender", "女性");                
        set("long", "契约[2;37;0m
它是夏鸥丸的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "felw");
        set("owner_name", "夏鸥丸");
        set_temp("owner", "felw");
        set_temp("owner_name", "夏鸥丸");
        ::setup();
}
