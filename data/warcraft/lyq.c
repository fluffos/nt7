// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("考虑到健[2;37;0m[2;37;0m", ({"cib"}));        
        set("gender", "男性");                
        set("long", "考虑到健[2;37;0m
它是樱桃七号的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lyq");
        set("owner_name", "樱桃七号");
        set_temp("owner", "lyq");
        set_temp("owner_name", "樱桃七号");
        ::setup();
}
