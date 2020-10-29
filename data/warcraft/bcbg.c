// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m卡哇伊[2;37;0m[2;37;0m", ({"chick"}));        
        set("gender", "男性");                
        set("long", "贵啊[2;37;0m
它是白菜饼干的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "bcbg");
        set("owner_name", "白菜饼干");
        set_temp("owner", "bcbg");
        set_temp("owner_name", "白菜饼干");
        ::setup();
}
