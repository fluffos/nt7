// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小宠物[2;37;0m[2;37;0m", ({"baoma"}));        
        set("gender", "男性");                
        set("long", "小宠物[2;37;0m
它是宠物大师的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "wuduguiji");
        set("owner_name", "宠物大师");
        set_temp("owner", "wuduguiji");
        set_temp("owner_name", "宠物大师");
        ::setup();
}
