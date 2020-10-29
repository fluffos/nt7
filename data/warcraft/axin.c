// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("星星[2;37;0m[2;37;0m", ({"xingxing"}));        
        set("gender", "女性");                
        set("long", "星星[2;37;0m
它是阿兴的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "axin");
        set("owner_name", "阿兴");
        set_temp("owner", "axin");
        set_temp("owner_name", "阿兴");
        ::setup();
}
