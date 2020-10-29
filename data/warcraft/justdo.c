// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[35m红鸟[2;37;0m[2;37;0m", ({"xiaonn"}));        
        set("gender", "男性");                
        set("long", "小[2;37;0m
它是幻梦的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "justdo");
        set("owner_name", "幻梦");
        set_temp("owner", "justdo");
        set_temp("owner_name", "幻梦");
        ::setup();
}
