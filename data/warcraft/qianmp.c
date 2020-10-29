// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("老马[2;37;0m[2;37;0m", ({"laoma"}));        
        set("gender", "男性");                
        set("long", "老马[2;37;0m
它是流绪微梦的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qianmp");
        set("owner_name", "流绪微梦");
        set_temp("owner", "qianmp");
        set_temp("owner_name", "流绪微梦");
        ::setup();
}
