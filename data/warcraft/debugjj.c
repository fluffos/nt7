// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuquejj"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是姓名十米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "debugjj");
        set("owner_name", "姓名十米");
        set_temp("owner", "debugjj");
        set_temp("owner_name", "姓名十米");
        ::setup();
}
