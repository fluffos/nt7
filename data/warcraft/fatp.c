// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽八[2;37;0m[2;37;0m", ({"aap"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是大药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatp");
        set("owner_name", "大药");
        set_temp("owner", "fatp");
        set_temp("owner_name", "大药");
        ::setup();
}
