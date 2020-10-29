// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("金乌[2;37;0m[2;37;0m", ({"old"}));        
        set("gender", "女性");                
        set("long", "金乌[2;37;0m
它是老妇的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "oldwoman");
        set("owner_name", "老妇");
        set_temp("owner", "oldwoman");
        set_temp("owner_name", "老妇");
        ::setup();
}
