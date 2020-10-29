// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("魔幻兽[2;37;0m[2;37;0m", ({"yaocs"}));        
        set("gender", "女性");                
        set("long", "我的魔幻兽[2;37;0m
它是撒份的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "yaoc");
        set("owner_name", "撒份");
        set_temp("owner", "yaoc");
        set_temp("owner_name", "撒份");
        ::setup();
}
