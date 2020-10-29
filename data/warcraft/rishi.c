// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m星月[2;37;0m[2;37;0m", ({"xingyue"}));        
        set("gender", "男性");                
        set("long", "拥星抱月[2;37;0m
它是日食的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "rishi");
        set("owner_name", "日食");
        set_temp("owner", "rishi");
        set_temp("owner_name", "日食");
        ::setup();
}
