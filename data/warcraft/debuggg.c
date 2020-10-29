// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuquegg"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是姓名七米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "debuggg");
        set("owner_name", "姓名七米");
        set_temp("owner", "debuggg");
        set_temp("owner_name", "姓名七米");
        ::setup();
}
