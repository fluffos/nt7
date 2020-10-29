// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m秃驴[2;37;0m[2;37;0m", ({"foxza"}));        
        set("gender", "男性");                
        set("long", "一只和尚骑的小毛驴[2;37;0m
它是皮皮猪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "foxz");
        set("owner_name", "皮皮猪");
        set_temp("owner", "foxz");
        set_temp("owner_name", "皮皮猪");
        ::setup();
}
