// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m吊筋白额大虫[2;37;0m[2;37;0m", ({"xxx"}));        
        set("gender", "男性");                
        set("long", "一头通体皆为白色的猛虎，威猛异常。[2;37;0m
它是周不痛的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "buton");
        set("owner_name", "周不痛");
        set_temp("owner", "buton");
        set_temp("owner_name", "周不痛");
        ::setup();
}
