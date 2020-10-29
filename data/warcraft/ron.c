// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[44;1m[1;36m太古[1;33m麒麟[1;31m圣皇[2;37;0m[2;37;0m", ({"antediluvian"}));        
        set("gender", "男性");                
        set("long", "太古时代麒麟一族的圣皇。它全身覆盖着厚实的鳞甲发出金色圣光。[2;37;0m
它是龙麟霸天的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ron");
        set("owner_name", "龙麟霸天");
        set_temp("owner", "ron");
        set_temp("owner_name", "龙麟霸天");
        ::setup();
}
