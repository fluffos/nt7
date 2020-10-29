// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m勾缘福[2;37;0m[2;37;0m", ({"kosfykpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是福缘勾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosfyk");
        set("owner_name", "福缘勾");
        set_temp("owner", "kosfyk");
        set_temp("owner_name", "福缘勾");
        ::setup();
}
