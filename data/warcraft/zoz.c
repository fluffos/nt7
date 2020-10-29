// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[44;1m[1;31m烽火连城[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "烽火连城[2;37;0m
它是武圣的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zoz");
        set("owner_name", "武圣");
        set_temp("owner", "zoz");
        set_temp("owner_name", "武圣");
        ::setup();
}
