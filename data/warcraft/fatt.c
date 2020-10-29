// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽饵[2;37;0m[2;37;0m", ({"aat"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是因药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatt");
        set("owner_name", "因药");
        set_temp("owner", "fatt");
        set_temp("owner_name", "因药");
        ::setup();
}
