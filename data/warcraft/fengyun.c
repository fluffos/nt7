// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m规规[2;37;0m[2;37;0m", ({"guigui"}));        
        set("gender", "女性");                
        set("long", "好大一只鸟！！~~~~好大一只鸟！！~~~~好大一只鸟啊！！~~~~l[2;37;0m
它是胡不归的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "fengyun");
        set("owner_name", "胡不归");
        set_temp("owner", "fengyun");
        set_temp("owner_name", "胡不归");
        ::setup();
}
