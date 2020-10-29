// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m捌福缘[2;37;0m[2;37;0m", ({"kosfyhpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是福缘捌的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kosfyh");
        set("owner_name", "福缘捌");
        set_temp("owner", "kosfyh");
        set_temp("owner_name", "福缘捌");
        ::setup();
}
