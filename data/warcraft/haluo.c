// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "hi[2;37;0m
它是肯克哈洛的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "haluo");
        set("owner_name", "肯克哈洛");
        set_temp("owner", "haluo");
        set_temp("owner_name", "肯克哈洛");
        ::setup();
}
