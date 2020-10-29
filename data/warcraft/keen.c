// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "旅行居家必备之物。[2;37;0m
它是科恩的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "keen");
        set("owner_name", "科恩");
        set_temp("owner", "keen");
        set_temp("owner_name", "科恩");
        ::setup();
}
