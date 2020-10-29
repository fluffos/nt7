// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("卡罗拉[2;37;0m[2;37;0m", ({"corolla"}));        
        set("gender", "女性");                
        set("long", "卡罗拉[2;37;0m
它是鸬咔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "luka");
        set("owner_name", "鸬咔");
        set_temp("owner", "luka");
        set_temp("owner_name", "鸬咔");
        ::setup();
}
