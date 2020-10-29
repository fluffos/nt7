// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuqueee"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是姓名五米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "debugee");
        set("owner_name", "姓名五米");
        set_temp("owner", "debugee");
        set_temp("owner_name", "姓名五米");
        ::setup();
}
