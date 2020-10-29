// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽四[2;37;0m[2;37;0m", ({"aal"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是您药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatl");
        set("owner_name", "您药");
        set_temp("owner", "fatl");
        set_temp("owner_name", "您药");
        ::setup();
}
