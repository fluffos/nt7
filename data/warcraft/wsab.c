// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("笨鸟[2;37;0m[2;37;0m", ({"eat_liang"}));        
        set("gender", "男性");                
        set("long", "@@@@[2;37;0m
它是小猪班班的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wsab");
        set("owner_name", "小猪班班");
        set_temp("owner", "wsab");
        set_temp("owner_name", "小猪班班");
        ::setup();
}
