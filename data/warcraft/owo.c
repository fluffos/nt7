// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m药袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "药袋[2;37;0m
它是圣丹师的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "owo");
        set("owner_name", "圣丹师");
        set_temp("owner", "owo");
        set_temp("owner_name", "圣丹师");
        ::setup();
}
