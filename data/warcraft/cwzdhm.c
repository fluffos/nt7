// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"zhuq"}));        
        set("gender", "女性");                
        set("long", "一只朱雀。[2;37;0m
它是素手锋芒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cwzdhm");
        set("owner_name", "素手锋芒");
        set_temp("owner", "cwzdhm");
        set_temp("owner_name", "素手锋芒");
        ::setup();
}
