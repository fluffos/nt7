// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m伍福缘[2;37;0m[2;37;0m", ({"kosfyepet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是福缘伍的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosfye");
        set("owner_name", "福缘伍");
        set_temp("owner", "kosfye");
        set_temp("owner_name", "福缘伍");
        ::setup();
}
