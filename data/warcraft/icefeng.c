// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小幼幼[2;37;0m[2;37;0m", ({"iceler"}));        
        set("gender", "女性");                
        set("long", "  [2;37;0m
它是冰灵风的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "icefeng");
        set("owner_name", "冰灵风");
        set_temp("owner", "icefeng");
        set_temp("owner_name", "冰灵风");
        ::setup();
}
