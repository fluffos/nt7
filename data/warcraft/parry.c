// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m苍[1;37m麟[2;37;0m[2;37;0m", ({"pdk"}));        
        set("gender", "男性");                
        set("long", "上古神兽之一[2;37;0m
它是帝如来的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "parry");
        set("owner_name", "帝如来");
        set_temp("owner", "parry");
        set_temp("owner_name", "帝如来");
        ::setup();
}
