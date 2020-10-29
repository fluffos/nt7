// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m药袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "药袋[2;37;0m
它是妖丹师的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wow");
        set("owner_name", "妖丹师");
        set_temp("owner", "wow");
        set_temp("owner_name", "妖丹师");
        ::setup();
}
