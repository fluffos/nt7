// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m幻[2;37;0m[2;37;0m", ({"dijun"}));        
        set("gender", "男性");                
        set("long", "呆头呆脑[2;37;0m
它是千回的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "qianhui");
        set("owner_name", "千回");
        set_temp("owner", "qianhui");
        set_temp("owner_name", "千回");
        ::setup();
}
