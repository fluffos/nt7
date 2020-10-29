// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m七小月份[2;37;0m[2;37;0m", ({"julya"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是七月份的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "july");
        set("owner_name", "七月份");
        set_temp("owner", "july");
        set_temp("owner_name", "七月份");
        ::setup();
}
