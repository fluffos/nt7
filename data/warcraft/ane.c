// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白鸟[2;37;0m[2;37;0m", ({"bniao"}));        
        set("gender", "男性");                
        set("long", "白鸟[2;37;0m
它是丹师一睛的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ane");
        set("owner_name", "丹师一睛");
        set_temp("owner", "ane");
        set_temp("owner_name", "丹师一睛");
        ::setup();
}
