// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"lidsa"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是星人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lids");
        set("owner_name", "星人");
        set_temp("owner", "lids");
        set_temp("owner_name", "星人");
        ::setup();
}
