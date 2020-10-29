// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "一只可以奔跑的睡袋。[2;37;0m
它是小聊的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xliao");
        set("owner_name", "小聊");
        set_temp("owner", "xliao");
        set_temp("owner_name", "小聊");
        ::setup();
}
