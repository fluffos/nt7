// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m毕方[2;37;0m[2;37;0m", ({"flame"}));        
        set("gender", "男性");                
        set("long", "星星之火，可以毁天灭地！[2;37;0m
它是最终信仰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "limitless");
        set("owner_name", "最终信仰");
        set_temp("owner", "limitless");
        set_temp("owner_name", "最终信仰");
        ::setup();
}
