// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("微微[2;37;0m[2;37;0m", ({"vivi"}));        
        set("gender", "女性");                
        set("long", "我的宝马[2;37;0m
它是归去来的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xtie");
        set("owner_name", "归去来");
        set_temp("owner", "xtie");
        set_temp("owner_name", "归去来");
        ::setup();
}
