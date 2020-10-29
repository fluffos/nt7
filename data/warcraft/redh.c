// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[35m睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "睡袋[2;37;0m
它是花莲老祖的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "redh");
        set("owner_name", "花莲老祖");
        set_temp("owner", "redh");
        set_temp("owner_name", "花莲老祖");
        ::setup();
}
