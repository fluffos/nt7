// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m小麟[31m[2;37;0m[2;37;0m", ({"xiaolin"}));        
        set("gender", "女性");                
        set("long", "带来好运的神兽[2;37;0m
它是风飞扬的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "seefly");
        set("owner_name", "风飞扬");
        set_temp("owner", "seefly");
        set_temp("owner_name", "风飞扬");
        ::setup();
}
