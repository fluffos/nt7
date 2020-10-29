// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m肆武[2;37;0m[2;37;0m", ({"matjpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是武肆的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "matk");
        set("owner_name", "武肆");
        set_temp("owner", "matk");
        set_temp("owner_name", "武肆");
        ::setup();
}
