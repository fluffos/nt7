// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m肆福缘[2;37;0m[2;37;0m", ({"kosfydpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是福缘肆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosfyd");
        set("owner_name", "福缘肆");
        set_temp("owner", "kosfyd");
        set_temp("owner_name", "福缘肆");
        ::setup();
}
