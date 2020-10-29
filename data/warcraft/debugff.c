// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuqueff"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是姓名六米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "debugff");
        set("owner_name", "姓名六米");
        set_temp("owner", "debugff");
        set_temp("owner_name", "姓名六米");
        ::setup();
}
