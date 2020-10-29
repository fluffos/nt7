// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;37m飞[31m龙[1;32m在[34m天[2;37;0m[2;37;0m", ({"flydragon"}));        
        set("gender", "女性");                
        set("long", "哈哈[2;37;0m
它是风飞扬的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hsa");
        set("owner_name", "风飞扬");
        set_temp("owner", "hsa");
        set_temp("owner_name", "风飞扬");
        ::setup();
}
