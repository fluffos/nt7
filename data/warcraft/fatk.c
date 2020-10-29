// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽三[2;37;0m[2;37;0m", ({"aak"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是入药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatk");
        set("owner_name", "入药");
        set_temp("owner", "fatk");
        set_temp("owner_name", "入药");
        ::setup();
}
