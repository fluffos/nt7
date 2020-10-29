// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽舞[2;37;0m[2;37;0m", ({"aaw"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是选药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatw");
        set("owner_name", "选药");
        set_temp("owner", "fatw");
        set_temp("owner_name", "选药");
        ::setup();
}
