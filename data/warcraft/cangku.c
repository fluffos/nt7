// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("青龙[2;37;0m[2;37;0m", ({"cangkux"}));        
        set("gender", "女性");                
        set("long", "一只小青虫[2;37;0m
它是仓库一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "cangku");
        set("owner_name", "仓库一");
        set_temp("owner", "cangku");
        set_temp("owner_name", "仓库一");
        ::setup();
}
