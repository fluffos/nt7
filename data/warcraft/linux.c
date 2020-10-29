// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火麒麟[2;37;0m[2;37;0m", ({"xuen"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是紫菜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "linux");
        set("owner_name", "紫菜");
        set_temp("owner", "linux");
        set_temp("owner_name", "紫菜");
        ::setup();
}
