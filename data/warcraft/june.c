// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m六小月份[2;37;0m[2;37;0m", ({"junea"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是六月份的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "june");
        set("owner_name", "六月份");
        set_temp("owner", "june");
        set_temp("owner_name", "六月份");
        ::setup();
}
