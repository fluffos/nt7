// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽五[2;37;0m[2;37;0m", ({"aamm"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是的药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatm");
        set("owner_name", "的药");
        set_temp("owner", "fatm");
        set_temp("owner_name", "的药");
        ::setup();
}
