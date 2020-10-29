// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"wahaha"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是雪碧的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sprite");
        set("owner_name", "雪碧");
        set_temp("owner", "sprite");
        set_temp("owner_name", "雪碧");
        ::setup();
}
