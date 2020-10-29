// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽九[2;37;0m[2;37;0m", ({"aaq"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是名药的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fatq");
        set("owner_name", "名药");
        set_temp("owner", "fatq");
        set_temp("owner_name", "名药");
        ::setup();
}
