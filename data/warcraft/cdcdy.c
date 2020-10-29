// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("朱雀[2;37;0m[2;37;0m", ({"cdcdypet"}));        
        set("gender", "男性");                
        set("long", "朱雀[2;37;0m
它是卢萨卡的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cdcdy");
        set("owner_name", "卢萨卡");
        set_temp("owner", "cdcdy");
        set_temp("owner_name", "卢萨卡");
        ::setup();
}
