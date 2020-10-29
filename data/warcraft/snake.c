// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "一个睡袋，江湖人士用来在野外睡觉用的。[2;37;0m
它是灰机的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "snake");
        set("owner_name", "灰机");
        set_temp("owner", "snake");
        set_temp("owner_name", "灰机");
        ::setup();
}
