// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuqueaa"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是姓名一米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "debugaa");
        set("owner_name", "姓名一米");
        set_temp("owner", "debugaa");
        set_temp("owner_name", "姓名一米");
        ::setup();
}
