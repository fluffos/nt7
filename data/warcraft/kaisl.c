// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "睡袋[2;37;0m
它是开塞露的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kaisl");
        set("owner_name", "开塞露");
        set_temp("owner", "kaisl");
        set_temp("owner_name", "开塞露");
        ::setup();
}
