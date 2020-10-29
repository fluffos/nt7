// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("坐骑宝宝[2;37;0m[2;37;0m", ({"zuoqibaobao"}));        
        set("gender", "女性");                
        set("long", "坐骑宝宝[2;37;0m
它是血剑盟的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "syshiyi");
        set("owner_name", "血剑盟");
        set_temp("owner", "syshiyi");
        set_temp("owner_name", "血剑盟");
        ::setup();
}
