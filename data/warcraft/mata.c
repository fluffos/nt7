// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m木甲[2;37;0m[2;37;0m", ({"matapet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是甲木的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mata");
        set("owner_name", "甲木");
        set_temp("owner", "mata");
        set_temp("owner_name", "甲木");
        ::setup();
}
