// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("幻世录[2;37;0m[2;37;0m", ({"baikx"}));        
        set("gender", "女性");                
        set("long", "魔幻兽[2;37;0m
它是白开心的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mifanc");
        set("owner_name", "白开心");
        set_temp("owner", "mifanc");
        set_temp("owner_name", "白开心");
        ::setup();
}
