// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m千足蜈蚣[2;37;0m[2;37;0m", ({"zao"}));        
        set("gender", "男性");                
        set("long", "千足蜈蚣[2;37;0m
它是毒殇的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "dudu");
        set("owner_name", "毒殇");
        set_temp("owner", "dudu");
        set_temp("owner_name", "毒殇");
        ::setup();
}
