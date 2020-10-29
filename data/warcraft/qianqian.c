// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m小毛驴[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "男性");                
        set("long", "小毛驴[2;37;0m
它是钱钱的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "qianqian");
        set("owner_name", "钱钱");
        set_temp("owner", "qianqian");
        set_temp("owner_name", "钱钱");
        ::setup();
}
