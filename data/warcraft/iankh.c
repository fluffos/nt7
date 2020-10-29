// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m咩咩[2;37;0m[2;37;0m", ({"horse"}));        
        set("gender", "男性");                
        set("long", "$HIY$咩咩[2;37;0m
它是风十七的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "iankh");
        set("owner_name", "风十七");
        set_temp("owner", "iankh");
        set_temp("owner_name", "风十七");
        ::setup();
}
