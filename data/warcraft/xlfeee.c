// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小红[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "女性");                
        set("long", "ＡＡＡＡＡ[2;37;0m
它是大黑的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xlfeee");
        set("owner_name", "大黑");
        set_temp("owner", "xlfeee");
        set_temp("owner_name", "大黑");
        ::setup();
}
