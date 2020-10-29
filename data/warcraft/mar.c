// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m三小月份[2;37;0m[2;37;0m", ({"mara"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是三月份的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mar");
        set("owner_name", "三月份");
        set_temp("owner", "mar");
        set_temp("owner_name", "三月份");
        ::setup();
}
