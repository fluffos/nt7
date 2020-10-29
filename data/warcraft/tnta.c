// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白麒麟[2;37;0m[2;37;0m", ({"tntnt"}));        
        set("gender", "女性");                
        set("long", "麒麟麒麟[2;37;0m
它是零零恭的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tnta");
        set("owner_name", "零零恭");
        set_temp("owner", "tnta");
        set_temp("owner_name", "零零恭");
        ::setup();
}
