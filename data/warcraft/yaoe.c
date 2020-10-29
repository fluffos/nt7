// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"yaoes"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是无份的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yaoe");
        set("owner_name", "无份");
        set_temp("owner", "yaoe");
        set_temp("owner_name", "无份");
        ::setup();
}
