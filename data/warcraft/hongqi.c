// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"myma"}));        
        set("gender", "男性");                
        set("long", "一只鲜红色的朱雀[2;37;0m
它是红旗的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hongqi");
        set("owner_name", "红旗");
        set_temp("owner", "hongqi");
        set_temp("owner_name", "红旗");
        ::setup();
}
