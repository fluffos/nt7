// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m家禽[2;37;0m[2;37;0m", ({"xianhe"}));        
        set("gender", "女性");                
        set("long", "家禽[2;37;0m
它是今天的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "today");
        set("owner_name", "今天");
        set_temp("owner", "today");
        set_temp("owner_name", "今天");
        ::setup();
}
