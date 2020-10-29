// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("追云[2;37;0m[2;37;0m", ({"yunfly"}));        
        set("gender", "女性");                
        set("long", "无[2;37;0m
它是百链生的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "towo");
        set("owner_name", "百链生");
        set_temp("owner", "towo");
        set_temp("owner_name", "百链生");
        ::setup();
}
