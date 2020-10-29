// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("情兽[2;37;0m[2;37;0m", ({"qing"}));        
        set("gender", "女性");                
        set("long", "情兽[2;37;0m
它是上官云的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "suyun");
        set("owner_name", "上官云");
        set_temp("owner", "suyun");
        set_temp("owner_name", "上官云");
        ::setup();
}
