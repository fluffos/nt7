// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("皮皮皮皮[2;37;0m[2;37;0m", ({"pppp"}));        
        set("gender", "女性");                
        set("long", "皮皮皮皮[2;37;0m
它是一起邦的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ichibang");
        set("owner_name", "一起邦");
        set_temp("owner", "ichibang");
        set_temp("owner_name", "一起邦");
        ::setup();
}
