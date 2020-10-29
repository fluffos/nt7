// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("西班牙[2;37;0m[2;37;0m", ({"aaac"}));        
        set("gender", "男性");                
        set("long", "西班牙[2;37;0m
它是中新的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zhong");
        set("owner_name", "中新");
        set_temp("owner", "zhong");
        set_temp("owner_name", "中新");
        ::setup();
}
