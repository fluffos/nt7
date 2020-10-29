// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("上要[2;37;0m[2;37;0m", ({"ctk"}));        
        set("gender", "女性");                
        set("long", "上要[2;37;0m
它是阵列的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "tkc");
        set("owner_name", "阵列");
        set_temp("owner", "tkc");
        set_temp("owner_name", "阵列");
        ::setup();
}
