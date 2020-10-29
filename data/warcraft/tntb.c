// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白麒麟[2;37;0m[2;37;0m", ({"tntnt"}));        
        set("gender", "女性");                
        set("long", "give kuang dizang zhishi[2;37;0m
它是零零喜的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "tntb");
        set("owner_name", "零零喜");
        set_temp("owner", "tntb");
        set_temp("owner_name", "零零喜");
        ::setup();
}
