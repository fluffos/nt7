// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白宝[2;37;0m[2;37;0m", ({"bai"}));        
        set("gender", "男性");                
        set("long", "巨型乖乖白虎[2;37;0m
它是大侠客的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "daxiake");
        set("owner_name", "大侠客");
        set_temp("owner", "daxiake");
        set_temp("owner_name", "大侠客");
        ::setup();
}
