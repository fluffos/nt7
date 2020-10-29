// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("练气[2;37;0m[2;37;0m", ({"lidjj"}));        
        set("gender", "男性");                
        set("long", "练气[2;37;0m
它是炼电的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidj");
        set("owner_name", "炼电");
        set_temp("owner", "lidj");
        set_temp("owner_name", "炼电");
        ::setup();
}
