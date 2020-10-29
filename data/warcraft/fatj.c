// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽而[2;37;0m[2;37;0m", ({"aaj"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是请药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatj");
        set("owner_name", "请药");
        set_temp("owner", "fatj");
        set_temp("owner_name", "请药");
        ::setup();
}
