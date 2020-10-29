// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m赤兔[2;37;0m[2;37;0m", ({"redtoo"}));        
        set("gender", "男性");                
        set("long", "$HIR$这就是来自西域的名驹赤兔[2;37;0m
它是周不嗵的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "buto");
        set("owner_name", "周不嗵");
        set_temp("owner", "buto");
        set_temp("owner_name", "周不嗵");
        ::setup();
}
