// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m七彩[1;35m琉璃兽[2;37;0m[2;37;0m", ({"qicai"}));        
        set("gender", "男性");                
        set("long", "七彩琉璃兽[2;37;0m
它是无名老人的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "noname");
        set("owner_name", "无名老人");
        set_temp("owner", "noname");
        set_temp("owner_name", "无名老人");
        ::setup();
}
