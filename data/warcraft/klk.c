// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("万岁走[2;37;0m[2;37;0m", ({"klkd"}));        
        set("gender", "女性");                
        set("long", "谁有[2;37;0m
它是六位数字的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "klk");
        set("owner_name", "六位数字");
        set_temp("owner", "klk");
        set_temp("owner_name", "六位数字");
        ::setup();
}
