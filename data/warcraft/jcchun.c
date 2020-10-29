// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("脑残兽脑残[2;37;0m[2;37;0m", ({"january"}));        
        set("gender", "男性");                
        set("long", "脑残[2;37;0m
它是俊儿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jcchun");
        set("owner_name", "俊儿");
        set_temp("owner", "jcchun");
        set_temp("owner_name", "俊儿");
        ::setup();
}
