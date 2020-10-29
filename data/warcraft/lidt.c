// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"lidsa"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是星是的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lidt");
        set("owner_name", "星是");
        set_temp("owner", "lidt");
        set_temp("owner_name", "星是");
        ::setup();
}
