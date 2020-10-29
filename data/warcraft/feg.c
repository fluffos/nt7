// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"fffff"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是何谢谢的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "feg");
        set("owner_name", "何谢谢");
        set_temp("owner", "feg");
        set_temp("owner_name", "何谢谢");
        ::setup();
}
