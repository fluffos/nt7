// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("宝马[2;37;0m[2;37;0m", ({"lidhh"}));        
        set("gender", "男性");                
        set("long", "宝马[2;37;0m
它是炼空的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidh");
        set("owner_name", "炼空");
        set_temp("owner", "lidh");
        set_temp("owner_name", "炼空");
        ::setup();
}
