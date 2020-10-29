// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("棒尼[2;37;0m[2;37;0m", ({"bangni"}));        
        set("gender", "女性");                
        set("long", "棒尼[2;37;0m
它是尼棒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nibang");
        set("owner_name", "尼棒");
        set_temp("owner", "nibang");
        set_temp("owner_name", "尼棒");
        ::setup();
}
