// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"fkbb"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是福北的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fkb");
        set("owner_name", "福北");
        set_temp("owner", "fkb");
        set_temp("owner_name", "福北");
        ::setup();
}
