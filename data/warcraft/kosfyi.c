// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m玖福缘[2;37;0m[2;37;0m", ({"kosfyipet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是福缘玖的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosfyi");
        set("owner_name", "福缘玖");
        set_temp("owner", "kosfyi");
        set_temp("owner_name", "福缘玖");
        ::setup();
}
