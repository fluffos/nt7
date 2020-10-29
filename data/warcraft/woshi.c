// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("书[2;37;0m[2;37;0m", ({"shui"}));        
        set("gender", "女性");                
        set("long", "书[2;37;0m
它是无金额的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "woshi");
        set("owner_name", "无金额");
        set_temp("owner", "woshi");
        set_temp("owner_name", "无金额");
        ::setup();
}
