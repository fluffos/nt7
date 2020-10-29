// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zqfdhfjhcxcqr"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是玄冰的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "flyc");
        set("owner_name", "玄冰");
        set_temp("owner", "flyc");
        set_temp("owner_name", "玄冰");
        ::setup();
}
