// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"yaoos"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是师份的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yaoo");
        set("owner_name", "师份");
        set_temp("owner", "yaoo");
        set_temp("owner_name", "师份");
        ::setup();
}
