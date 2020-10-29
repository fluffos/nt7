// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("交换机[2;37;0m[2;37;0m", ({"idsds"}));        
        set("gender", "女性");                
        set("long", "交换机叫姐姐[2;37;0m
它是哦点的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lqxb");
        set("owner_name", "哦点");
        set_temp("owner", "lqxb");
        set_temp("owner_name", "哦点");
        ::setup();
}
