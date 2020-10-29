// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小眼[2;37;0m[2;37;0m", ({"myzuoqi"}));        
        set("gender", "女性");                
        set("long", "小眼[2;37;0m
它是卡共巨化的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nno");
        set("owner_name", "卡共巨化");
        set_temp("owner", "nno");
        set_temp("owner_name", "卡共巨化");
        ::setup();
}
