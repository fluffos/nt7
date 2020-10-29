// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m兜[1;33m兜[1;32m猫[2;37;0m[2;37;0m", ({"doudoumao"}));        
        set("gender", "女性");                
        set("long", "一只可爱的小猫，身上有个小兜兜，里卖装满了各种零食。[2;37;0m
它是刃无缺的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "baleno");
        set("owner_name", "刃无缺");
        set_temp("owner", "baleno");
        set_temp("owner_name", "刃无缺");
        ::setup();
}
