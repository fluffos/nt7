// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m柒福缘[2;37;0m[2;37;0m", ({"kosfygpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是福缘柒的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosfyg");
        set("owner_name", "福缘柒");
        set_temp("owner", "kosfyg");
        set_temp("owner_name", "福缘柒");
        ::setup();
}
