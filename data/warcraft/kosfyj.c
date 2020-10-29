// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m拾缘福[2;37;0m[2;37;0m", ({"kosfyjpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是福缘拾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosfyj");
        set("owner_name", "福缘拾");
        set_temp("owner", "kosfyj");
        set_temp("owner_name", "福缘拾");
        ::setup();
}
