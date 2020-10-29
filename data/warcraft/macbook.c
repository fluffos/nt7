// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m苹果手机[2;37;0m[2;37;0m", ({"iphone"}));        
        set("gender", "男性");                
        set("long", "$HIR$苹果手机[2;37;0m
它是苹果电脑的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "macbook");
        set("owner_name", "苹果电脑");
        set_temp("owner", "macbook");
        set_temp("owner_name", "苹果电脑");
        ::setup();
}
