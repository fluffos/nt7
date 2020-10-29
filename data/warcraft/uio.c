// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"esd"}));        
        set("gender", "女性");                
        set("long", "数学[2;37;0m
它是余育的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "uio");
        set("owner_name", "余育");
        set_temp("owner", "uio");
        set_temp("owner_name", "余育");
        ::setup();
}
