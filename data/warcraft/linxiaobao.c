// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "uptime[2;37;0m
它是林小宝的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "linxiaobao");
        set("owner_name", "林小宝");
        set_temp("owner", "linxiaobao");
        set_temp("owner_name", "林小宝");
        ::setup();
}
