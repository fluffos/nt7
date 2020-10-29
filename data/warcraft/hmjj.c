// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小虫[2;37;0m[2;37;0m", ({"jjkkll"}));        
        set("gender", "女性");                
        set("long", "可怜虫[2;37;0m
它是胡呆的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hmjj");
        set("owner_name", "胡呆");
        set_temp("owner", "hmjj");
        set_temp("owner_name", "胡呆");
        ::setup();
}
